/*
 * instructions.c
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#include "ctype.h"

#include "stdio.h"
#include "parser.h"
#include "constants.h"
#include "instructions.h"
#include "opcodes.h"

INSTRUCTION instruction;

void doInstruction(FILE* file) {

	char buffer[MAX_TOKEN_SIZE];

	readIdent(file, buffer);

	int ins = findInstruction(buffer);

	printf("Instruction: ");
	if (ins == OP_NOT_FOUND) {
		printf("UNKNOWN %s\n", buffer);
		skipLine(file);
		return;
	} else {

		printf("%s\n", buffer);

		instruction.ins = ins;

		int param = 0;

		//parse up to 3 params
		for (param = 0; param < 3; param++) {

			if (chrLookAhead == '\n') {
				break;
			}

			if (chrLookAhead == ',') {
				readChar(file);
				skipWhitespace(file);
			}

			//Something exists after the instruction
			char op1Buffer[MAX_TOKEN_SIZE];
			if (isdigit(chrLookAhead)) {
				//A Number
				readNumber(file, op1Buffer);
			} else if (isalpha(chrLookAhead) || chrLookAhead == '_') {
				//A DEFINE name
				readIdent(file, op1Buffer);
			} else if (chrLookAhead == '[') {
				//A Memory Address Operand
				//These are denoted by square brackets
				readChar(file); //Eat '['
				skipWhitespace(file);

				//A memory address can contain a number, or a identifier
				if (isdigit(chrLookAhead)) {
					readNumber(file, op1Buffer);
				} else {
					readIdent(file, op1Buffer);
				}

				readChar(file); //eat ']'
			}

			skipWhitespace(file);
		}
	}
}
