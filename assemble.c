/*
 * assemble.c
 *
 *  Created on: Mar 11, 2015
 *      Author: HICKSK
 */

#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

#include "globals.h"
#include "assemble.h"
#include "parser.h"
#include "directives.h"
#include "instructions.h"
#include "opcodes.h"
#include "expressions.h"

//Perform Pass1. Looking for Preprocessor directives
void pass1();
//Perform Pass2. Assemble instructions, output to output file & listing file
void pass2();
//During pass 2, we may break up the code into chuncks to better find the most effecient forms of reletive displacements
int assembleBlock();

void beginAssembly() {

	context.unifiedFile->file = fopen("testFiles\\test.uni", "w+");
	context.listingFile->file = fopen("testFiles\\test.lst", "w+");
	context.outputFile->file = fopen("testFiles\\test.out", "w+b");

	context.firstLabelEntry = NULL;
	context.firstMacroEntry = NULL;
	context.fileDepth = 1;
	context.bitMode = CTX_BITS_DEFAULT;
}

void endAssembly() {
	fclose(context.unifiedFile->file);
	fclose(context.listingFile->file);
	fclose(context.outputFile->file);
}

void assembleFile(char* fileName) {
	FILECONTEXT newFileContext;

	newFileContext.file = fopen(fileName, "r");
	newFileContext.lineNumber = 0;
	newFileContext.charNumber = 1;

	//Point the new filesContexts parent to the previous file
	newFileContext.parentFile = context.currFile;

	//And set the newFileContext as the current file
	context.currFile = &newFileContext;

	printf("Pass 1\n");
	pass1(); //Read & Store Macros, symbolic constants, and handle includes

	printf("Pass 2\n");
	pass2();	//Assemble & Output

	fclose(newFileContext.file);

	//revert back to the previous parent file, so that processing may continue
	context.currFile = newFileContext.parentFile;

	printf("Assemble Complete: %s\n", fileName);
}

void pass1() {
	//Prime pump
	readCharIntoBuffer();
	readLineIntoBuffer();
	while (tokens[currTokenIndex][0] != '\0') {

		if (findDirective(tokens[currTokenIndex], DRTV_ANY) != DRTV_NOT_FOUND) {
			//Process INCLUDE directives
			//Store MACROs in our table
			currTokenIndex++;
		} else if (findInstruction(tokens[currTokenIndex]) == INS_NOT_FOUND) {

			//Add label names to our table
			addLabelName(tokens[currTokenIndex], 0);
		}

		fprintf(context.unifiedFile->file, "%s\n", context.currFile->lineBuffer);

		readLineIntoBuffer();
	}
}

void pass2() {

	//Point CurrFile to the Unified file
	context.currFile->file = context.unifiedFile->file;

	//reset Counters
	context.currFile->lineNumber = 0;
	context.currFile->charNumber = 1;
	context.outputPos = 0;

	inFilePos = 0;
	outFilePos = 0;
	lstFilePos = 0;
	preInsAddr = 0;

	//Start back at the beginning of the file
	rewind(context.currFile->file);

	//Prime pump
	readCharIntoBuffer();

	assembleBlock();

	//make sure the listing file's write pointer is at the end
	fseek(context.listingFile->file, 0, SEEK_END);

	emitLabelsToListing();
}

void assembleLine() {
	currTokenIndex = 0;
	startOfComparison:

	//read the first label/instruction/macro etc
	if (findDirective(tokens[currTokenIndex], DRTV_PHASE1) != DRTV_NOT_FOUND) {
		//Handle appropriate directives
		int drtv = findDirective(tokens[currTokenIndex++], DRTV_PHASE1);

		switch (drtv) {
			case DRTV_BASE:

				context.outputPos = atol(tokens[currTokenIndex++]);

				break;
			case DRTV_BITS:
				/*
				 int bits = atol(tokens[currTokenIndex++]);
				 if (bits != 16 && bits != 32) {
				 expect("16 or 32 bits");
				 }

				 context.currFile->bitMode = bits;
				 break;
				 */
			case DRTV_DB:
				doDeclareBytes(1);
				break;
			case DRTV_DW:
				doDeclareBytes(2);
				break;
			case DRTV_DD:
				doDeclareBytes(4);
				break;
			case DRTV_DQ:
				doDeclareBytes(8);
				break;
		}

	} else if (findInstruction(tokens[currTokenIndex]) != INS_NOT_FOUND) {
		doInstruction();
		populateInstructionBytes();
	} else {
		setLabelPosition(tokens[currTokenIndex], context.outputPos);
		currTokenIndex++;

		//Optional Colon follows label
		if (tokens[currTokenIndex][0] == ':') {
			currTokenIndex++;
		}

		//Something after label
		if (tokens[currTokenIndex][0] != '\0') {
			currTokenIndex++;
			goto startOfComparison;
		}
	}
}

void outputLine(int toOutFile, int toListingFile) {

	if (toOutFile) {
		//Output to executable
		fwrite(instruction.byteArray,
				1,
				instruction.byteArrayCount,
				context.outputFile->file);

	}

	if (toListingFile) {
		//Output to Listing
		fprintf(context.listingFile->file, "0x%08X ", context.outputPos);					//The binary position
		fprintf(context.listingFile->file, "%s\n", context.currFile->lineBuffer); 		//source code, remove the line numbers

		//If we have anything to add to the listing from the output buffer
		if (instruction.byteArrayCount > 0) {
			fprintf(context.listingFile->file, "0x%08X   ", context.outputPos);					//The binary position

			int outIndex = 0;
			for (outIndex = 0; outIndex < instruction.byteArrayCount; outIndex++) {
				fprintf(context.listingFile->file, "%02X ", instruction.byteArray[outIndex] & 0xFF);	//hex representation of binary output
			}
			fprintf(context.listingFile->file, "\n");
		}

		//Add the current instruction bytes to the counter
		context.outputPos += instruction.byteArrayCount;
	}
}
int assembleBlock() {

	int tempInFilePos = ftell(context.currFile->file) - 1;
	int tempOutFilePos = ftell(context.outputFile->file);
	int tempLstFilePos = ftell(context.listingFile->file);
	int tempPreInsAddr = context.outputPos;

	readLineIntoBuffer();

	while (tokens[currTokenIndex][0] != '\0') {
		//inFilePos = ftell(context.currFile->file) - 1;
		//outFilePos = ftell(context.outputFile->file);
		//lstFilePos = ftell(context.listingFile->file);
		//preInsAddr = context.outputPos;

		instruction.byteArrayCount = 0;

		assembleLine();

		outputLine(TRUE, TRUE);

		int byteCount = instruction.byteArrayCount;

		if (forwardRefFound) {
			forwardRefFound = FALSE;

			printf("Context switch\n");
			assembleBlock();

			//move counters back
			fseek(context.currFile->file, tempInFilePos, SEEK_SET);
			fseek(context.outputFile->file, tempOutFilePos, SEEK_SET);
			fseek(context.listingFile->file, tempLstFilePos, SEEK_SET);
			context.outputPos = tempPreInsAddr;

			readCharIntoBuffer();
			readLineIntoBuffer();

			assembleLine();

			outputLine(TRUE, TRUE);

			//If our attempt worked, the output, and return
			if (instruction.byteArrayCount == byteCount) {
				return 0;
			}
			//otherwise keep assembling

		} else {

			readLineIntoBuffer();
		}
	}

	return 0;
}
