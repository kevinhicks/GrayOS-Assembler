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

	printf("Assembler\n");

	char* fileName = "testFiles\\test.src";
	assemble(fileName);

	return 0;
}

void assemble(char* fileName) {

	printf("Assembling: %s\n", fileName);

	FILE* file;

	insideQuotes = FALSE;


	file = fopen(fileName, "r");

	//prime the pump
	readChar(file);
	skipWhitespaceLines(file);

	while (chrLookAhead != EOF) {
		if (chrLookAhead == ';') {
			//Comment
			skipLine(file);
		} else if (chrLookAhead == ',') {
			//TODO Handle multiple parameters
			readChar(file);
			skipWhitespace(file);
		} else if (chrLookAhead == '#') {
			//Directive
			doDirective(file);
		} else {
			//Instruction
			doInstruction(file);
		}

		skipWhitespaceLines(file);
	}
	fclose(file);

	printf("Assemble Complete\n");
}

