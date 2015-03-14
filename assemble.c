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

//Psuedocode
//Pass 0
//	Read each line of input file until EOF
//	If line contains MACRO
//		Read & store in lok up table
//	rewind to start of input file
//
//Pass 1
//	Read each line of input file until EOF
//		If macro, expand.
//		If variable, store in lookup table
//		Count bytes of output
//	Output to temp file
//	rewind to start of input file
//
//Pass 2
//	Read each line of temp file until EOF
//		Assemble line
//		output binary to output file
//		output listing to l

void beginAssembly() {

	context.unifiedFile->file = fopen("testFiles\\test.uni", "w+");
	context.interFile->file = fopen("testFiles\\test.int", "w+");
	context.listingFile->file = fopen("testFiles\\test.lst", "w+");
	context.outputFile->file = fopen("testFiles\\test.out", "w+");

	context.firstLabelEntry = NULL;
	context.firstMacroEntry = NULL;
	context.fileDepth = 1;
}

void endAssembly() {
	fclose(context.unifiedFile->file);
	fclose(context.interFile->file);
	fclose(context.listingFile->file);
	fclose(context.outputFile->file);
}

void assembleFile(char* fileName) {
	FILECONTEXT newFileContext;
	INSTRUCTION ins;

	newFileContext.file = fopen(fileName, "r");
	newFileContext.lineNumber = 0;
	newFileContext.charNumber = 1;
	newFileContext.insDesc = &ins;

	//Point the new filesContexts parent to the previous file
	newFileContext.parentFile = context.currFile;

	//And set the newFileContext as the current file
	context.currFile = &newFileContext;

	printf("Pass 0\n");
	pass0(); //Read & Store Macros, symbolic constants, and handle includes

	printf("Pass 1\n");
	pass1();	//Expand Macros & Count Instructions

	printf("Pass 2\n");
	pass2();	//Assemble & Output

	fclose(newFileContext.file);

	//revert back to the previous parent file, so that processing may continue
	context.currFile = newFileContext.parentFile;

	printf("Assemble Complete: %s\n", fileName);
}

void pass0() {

	//Prime pump
	readCharIntoBuffer();
	while (context.currFile->lineBufferLookAhead != EOF) {
		readLineIntoBuffer();

		if (context.currFile->lookAhead != '\0') {

			/*
			 readIdent(context);
			 if (context.currFile->lookAhead == ':') {
			 //THis is a label
			 addLabel(context, context.currFile->tokenBuffer);
			 }
			 int directive = findDirective(context.currFile->tokenBuffer);

			 if (directive != DRTV_NOT_FOUND) {
			 doDirective(directive, context);
			 }
			 */
		}

		fprintf(context.unifiedFile->file, "%s\n", context.currFile->lineBuffer);
	}
}

void pass1() {

	//Point CurrFile to the Unified file
	context.currFile->file = context.unifiedFile->file;

	//reset Counters
	context.currFile->lineNumber = 0;
	context.currFile->charNumber = 1;
	context.outputPos = 0;

	//Start back at the beginning of the file
	rewind(context.currFile->file);

	//Prime pump
	readCharIntoBuffer();
	while (context.currFile->lineBufferLookAhead != EOF) {
		readLineIntoBuffer();

		int pos = context.outputPos;

		//A non-empty line
		if (context.currFile->lookAhead != '\0') {
			//read the first label/instruction/macro etc
			readIdent();
			if (context.currFile->lookAhead == ':') {
				//This is a label
				addLabel(context.currFile->tokenBuffer, context.outputPos);
			} else if (findDirective(context.currFile->tokenBuffer, DRTV_ANY) != DRTV_NOT_FOUND) {
				//Handle appropriate directives
				int i =2;

			} else if (findInstruction(context.currFile->tokenBuffer) != INS_NOT_FOUND) {
				//Try to assemble it
				//context.outputPos +=

				context.currFile->insDesc->byteArrayCount = 0;
				doInstruction();
				populateInstructionBytes();
				context.outputPos += context.currFile->insDesc->byteArrayCount;
			}

		}
		fprintf(context.interFile->file, "0x%08X  %s\n", pos, context.currFile->lineBuffer);
	}
}

void pass2() {

	//Point CurrFile to the Intermediate file
	context.currFile->file = context.interFile->file;

	//reset Counters
	context.currFile->lineNumber = 0;
	context.currFile->charNumber = 1;
	context.outputPos = 0;

	//Start back at the beginning of the file
	rewind(context.currFile->file);

	//Prime pump
	readCharIntoBuffer();
	while (context.currFile->lineBufferLookAhead != EOF) {
		readLineIntoBuffer();

		context.currFile->insDesc->byteArrayCount = 0;

		readNumber();	//This is the position in then binary our current instruction is reside at
		context.outputPos = context.currFile->numberTokenValue;

		//A non-empty line
		if (context.currFile->lookAhead != '\0') {
			//read the first instruction
			readIdent();
			if (context.currFile->lookAhead == ':') {
				//This is a label
				addLabel(context.currFile->tokenBuffer, context.outputPos);
			} else if (findDirective(context.currFile->tokenBuffer, DRTV_ANY) != DRTV_NOT_FOUND) {
				//Handle appropriate directives
			} else if (findInstruction(context.currFile->tokenBuffer) != INS_NOT_FOUND) {
				doInstruction();			//Parse & Classify instruction
				populateInstructionBytes();	//Store bytes in output buffer
			}

		}

		//Listing
		fprintf(context.listingFile->file, "0x%08X ", context.outputPos);					//The binary position
		fprintf(context.listingFile->file, "%s\n", context.currFile->lineBuffer + 12); 		//source code, remove the line numbers

		//If we have anything to add to the listing from the output buffer
		if (context.currFile->insDesc->byteArrayCount > 0) {
			fprintf(context.listingFile->file, "0x%08X   ", context.outputPos);					//The binary position

			int outIndex = 0;
			for (outIndex = 0; outIndex < context.currFile->insDesc->byteArrayCount; outIndex++) {
				fprintf(context.listingFile->file, "%02X ", context.currFile->insDesc->byteArray[outIndex] & 0xFF);	//hex representation of binary output
			}
			fprintf(context.listingFile->file, "\n");
		}
	}
	emitLabelsToListing();
}

void emitLabelsToListing() {
	fprintf(context.listingFile->file, "\n\nLABELS:\n");

	LABELTABLEENTRY* head = context.firstLabelEntry;

	while (head != NULL) {
		fprintf(context.listingFile->file, "%-10s %08X\n", head->name, head->position);

		head = head->nextEntry;
	}
}

void addLabel(char* labelName, int position) {
	LABELTABLEENTRY* tail = context.firstLabelEntry;

	if (tail == NULL) {
		context.firstLabelEntry = malloc(sizeof(LABELTABLEENTRY));
		tail = context.firstLabelEntry;
	} else {
		while (tail->nextEntry != NULL) {
			tail = tail->nextEntry;
		}
		tail->nextEntry = malloc(sizeof(LABELTABLEENTRY));
		tail = tail->nextEntry;
	}

	strcpy(tail->name, labelName);
	tail->position = position;
	tail->nextEntry = NULL;
}

