/*
 * instructions.c
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#include "ctype.h"
#include "stdlib.h"

#include "stdio.h"
#include "parser.h"
#include "constants.h"
#include "instructions.h"
#include "opcodes.h"

PARAMETER classifyNumber(char* buffer) {
	PARAMETER param;

	strcpy(&param.op, buffer);

	int number = atoi(buffer);

	if (number >> 8 == 0) {
		param.opSize = OP_SIZE_8;
		param.opType = OP_IMM8;
	}

	if (number >> 8 == 0) {
		param.opSize = OP_SIZE_16;
		param.opType = OP_IMM16;
	} else {
		param.opSize = OP_SIZE_32;
		param.opType = OP_IMM32;
	}

	return param;
}

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
	}

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
			instruction.op[param] = classifyNumber(op1Buffer);
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

	//Now try to match what we found to an entry in our table
findInstructionByOperands(instruction);

}
