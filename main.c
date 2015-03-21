/*
 * main.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stddef.h"

#include "parser.h"
#include "constants.h"
#include "opcodes.h"
#include "directives.h"
#include "instructions.h"
#include "assemble.h"
#include "utils.h"
#include "expressions.h"

ASSEMBLECONTEXT context;

void assembleBlock();

int main() {
	char* inputFileName = "testFiles\\test.src";

	FILECONTEXT unifiedFile;
	FILECONTEXT interFile;
	FILECONTEXT outputFile;
	FILECONTEXT listingFile;

	context.unifiedFile = &unifiedFile;
	context.interFile = &interFile;
	context.outputFile = &outputFile;
	context.listingFile = &listingFile;

	beginAssembly();
	//assembleFile(inputFileName);

	FILECONTEXT newFileContext;
	INSTRUCTION ins;

	newFileContext.file = fopen(inputFileName, "r");
	newFileContext.lineNumber = 0;
	newFileContext.charNumber = 1;
	newFileContext.insDesc = &ins;
	newFileContext.bitMode = CTX_BITS_DEFAULT;

	//Point the new filesContexts parent to the previous file
	newFileContext.parentFile = context.currFile;

	//And set the newFileContext as the current file
	context.currFile = &newFileContext;
	readCharIntoBuffer();
	assembleBlock();

	endAssembly();
	return 0;
}

int RelInstructions[][20] = {
		{ INS_JMP, 8, 2, 16, 3, 32, 5 }
};

void assembleBlock() {
	int inFileLoc = ftell(context.currFile->file);

	readLineIntoBuffer();

	while (context.currFile->lookAhead != '\0') {
		if (isalpha(context.currFile->lookAhead)) {
			readIdent();

			forwardRefFound = FALSE;

			int ins = findInstruction(context.currFile->tokenBuffer);
			if (ins != INS_NOT_FOUND)
			{
				printf("%s ", context.currFile->tokenBuffer);
				printf("%d ", expression());

				if (context.currFile->lookAhead == ',') {
					readChar();
					printf(", %d ", expression());
				}

				if (context.currFile->lookAhead == ',') {
					readChar();
					printf(", %d ", expression());
				}

				if(forwardRefFound) {
					printf("Her");
				}

				printf("\n");

			} else {
				printf("Label: %s found on line: %d\n", context.currFile->tokenBuffer, context.currFile->lineNumber);
				addLabelName(context.currFile->tokenBuffer, 1);
				setLabelPosition(context.currFile->tokenBuffer, 1);
			}
		}

		readLineIntoBuffer();
	}
}

