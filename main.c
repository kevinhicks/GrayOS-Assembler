/*
 * main.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "stdio.h"
#include "string.h"
#include "ctype.h"

#include "parser.h"
#include "constants.h"
#include "opcodes.h"
#include "directives.h"
#include "instructions.h"

void assemble(char* fileName);

int main() {
	char* fileName = "testFiles\\test.src";
	assemble(fileName);

	return 0;
}

void assemble(char* fileName) {

	printf("Assembling: %s\n", fileName);

	FILECONTEXT fileContext;

	fileContext.file = fopen(fileName, "r");
	fileContext.lineNumber = 1;
	fileContext.charNumber = 1;

	//prime the pump
	readChar(&fileContext);
	skipWhitespaceLines(&fileContext);

	while (fileContext.lookAhead != EOF) {
		if (fileContext.lookAhead == ';') {
			//Comment
			skipLine(&fileContext);
		} else if (fileContext.lookAhead == ',') {
			//TODO Handle multiple parameters
			readChar(&fileContext);
			skipWhitespace(&fileContext);
		} else if (fileContext.lookAhead == '#') {
			//Directive
			doDirective(&fileContext);
		} else {
			//Instruction
			doInstruction(&fileContext);
		}

		skipWhitespaceLines(&fileContext);
	}
	fclose(fileContext.file);

	printf("Assemble Complete\n");
}

