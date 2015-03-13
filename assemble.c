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

void beginAssembly(ASSEMBLECONTEXT* context) {

	context->unifiedFile->file = fopen("testFiles\\test.uni", "w+");
	context->interFile->file = fopen("testFiles\\test.int", "w+");
	context->listingFile->file = fopen("testFiles\\test.lst", "w+");
	context->outputFile->file = fopen("testFiles\\test.out", "w+");

	context->firstLabelEntry = NULL;
	context->firstMacroEntry = NULL;
	context->fileDepth = 1;
}

void endAssembly(ASSEMBLECONTEXT* context) {
	fclose(context->unifiedFile->file);
	fclose(context->interFile->file);
	fclose(context->listingFile->file);
	fclose(context->outputFile->file);
}

void assembleFile(ASSEMBLECONTEXT* assembleContext, char* fileName) {
	FILECONTEXT newFileContext;
	INSTRUCTION ins;

	newFileContext.file = fopen(fileName, "r");
	newFileContext.lineNumber = 0;
	newFileContext.charNumber = 1;
	newFileContext.insDesc = &ins;

	//Point the new filesContexts parent to the previous file
	newFileContext.parentFile = assembleContext->currFile;

	//And set the newFileContext as the current file
	assembleContext->currFile = &newFileContext;

	printf("Pass 0\n");
	pass0(assembleContext); //Read & Store Macros, symbolic constants, and handle includes

	printf("Pass 1\n");
	pass1(assembleContext);	//Expand Macros & Count Instructions

	printf("Pass 2\n");
	pass2(assembleContext);	//Assemble & Output

	fclose(newFileContext.file);

	//revert back to the previous parent file, so that processing may continue
	assembleContext->currFile = newFileContext.parentFile;

	printf("Assemble Complete: %s\n", fileName);
}

void pass0(ASSEMBLECONTEXT* context) {

	//Prime pump
	readCharIntoBuffer(context);
	while (context->currFile->lineBufferLookAhead != EOF) {
		readLineIntoBuffer(context);

		if (context->currFile->lookAhead != '\0') {

			/*
			 readIdent(context);
			 if (context->currFile->lookAhead == ':') {
			 //THis is a label
			 addLabel(context, context->currFile->tokenBuffer);
			 }
			 int directive = findDirective(context->currFile->tokenBuffer);

			 if (directive != DRTV_NOT_FOUND) {
			 doDirective(directive, context);
			 }
			 */
		}

		fprintf(context->unifiedFile->file, "%s\n", context->currFile->lineBuffer);
	}
}

void pass1(ASSEMBLECONTEXT* context) {

	context->currFile->file = context->unifiedFile->file;

	context->currFile->lineNumber = 0;
	context->currFile->charNumber = 1;
	context->outputPos = 0;

	rewind(context->currFile->file);
	//Prime pump
	readCharIntoBuffer(context);
	while (context->currFile->lineBufferLookAhead != EOF) {
		readLineIntoBuffer(context);

		int pos = context->outputPos;

		//A non-empty line
		if (context->currFile->lookAhead != '\0') {
			//read the first label/instruction/macro etc
			readIdent(context);
			if (context->currFile->lookAhead == ':') {
				//This is a label
				addLabel(context, context->currFile->tokenBuffer);
			} else if (findDirective(context->currFile->tokenBuffer, DRTV_PHASE1) != DRTV_NOT_FOUND) {
				//Handle appropriate directives
			} else if (findInstruction(context->currFile->tokenBuffer) != INS_NOT_FOUND) {
				//Try to assemble it
				//context->outputPos +=

				int* opcode = doInstruction(context, DO_INS_PHASE_COUNT);

				context->outputPos += countOpcodeBytes(context, opcode);
			}

		}
		fprintf(context->interFile->file, "0x%08X  %s\n", pos, context->currFile->lineBuffer);
		//Look For Define, or MACRO
	}
}

void pass2(ASSEMBLECONTEXT* context) {
	context->outputPos = 0;

	emitLabelsToListing(context);
}

void emitLabelsToListing(ASSEMBLECONTEXT* context) {
	fprintf(context->listingFile->file, "LABELS:\n");

	LABELTABLEENTRY* head = context->firstLabelEntry;

	while (head != NULL) {
		fprintf(context->listingFile->file, "%-10s %d\n", head->name, head->position);

		head = head->nextEntry;
	}
}

void addLabel(ASSEMBLECONTEXT* context, char* labelName) {
	LABELTABLEENTRY* tail = context->firstLabelEntry;

	if (tail == NULL) {
		context->firstLabelEntry = malloc(sizeof(LABELTABLEENTRY));
		tail = context->firstLabelEntry;
	} else {
		while (tail->nextEntry != NULL) {
			tail = tail->nextEntry;
		}
		tail->nextEntry = malloc(sizeof(LABELTABLEENTRY));
		tail = tail->nextEntry;
	}

	strcpy(tail->name, labelName);
	tail->position = context->outputPos;
	tail->nextEntry = NULL;
}
