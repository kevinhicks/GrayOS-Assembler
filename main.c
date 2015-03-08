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
	INSTRUCTION ins;

	file = fopen(fileName, "r");

	//prime the pump
	readChar(file);
	skipWhitespace(file);

	char buffer[MAX_WORD_SIZE];

	while (chrLookAhead != EOF) {
		if (chrLookAhead == ';') {
			printf("Comment Found\n");
			skipLine(file);
		} else if (chrLookAhead == ',') {
			readChar(file);
			skipWhitespace(file);
		} else if (chrLookAhead == '#') {
			doDirective(file);
			continue;
		} else {
			doInstruction(file);
		}
	}

	/*{

	 if (chrLookAhead == '[') {

	 } else {
	 char word[MAX_WORD_SIZE];
	 readWord(file, word);

	 int instruction = findInstruction(word);

	 //this is a instruction
	 if (instruction != OP_NOT_FOUND) {

	 printf("Look ahead after finding ins '%c'\n", chrLookAhead);

	 }
	 }
	 }
	 */
	fclose(file);
}

