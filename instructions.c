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

#include "string.h"

#include "stdlib.h"

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

void doInstruction(FILECONTEXT* context) {

	readIdent(context);

	int ins = findInstruction(context->tokenBuffer);

	printf("Instruction: ");
	if (ins == OP_NOT_FOUND) {
		printf("UNKNOWN %s\n", context->tokenBuffer);
		skipLine(context);
		return;
	}

	printf("%s\n", context->tokenBuffer);

	instruction.ins = ins;

	int param = 0;

	//parse up to 3 params
	for (param = 0; param < 3; param++) {

		if (context->lookAhead == '\n' || context->lookAhead == EOF) {
			break;
		}

		if (param > 0) {
			if (context->lookAhead == ',') {
				readChar(context); //Eat comma
				skipWhitespace(context);
			} else {
				expect(context, "',' or newline");
			}
		}

		//Something exists after the instruction
		char op1Buffer[MAX_TOKEN_SIZE];

		if (isdigit(context->lookAhead)) {
			//A Number
			readNumber(context);
			instruction.op[param] = classifyNumber(context->tokenBuffer);
		} else if (isalpha(context->lookAhead) || context->lookAhead == '_') {
			//A DEFINE name
			readIdent(context);
		} else if (context->lookAhead == '[') {
			//A Memory Address Operand
			//These are denoted by square brackets
			readChar(context); //Eat '['
			skipWhitespace(context);

			//A memory address can contain a number, or a identifier
			if (isdigit(context->lookAhead)) {
				readNumber(context);
			} else {
				readIdent(context);
			}

			readChar(context); //eat ']'
		}

		skipWhitespace(context);
	}

	//Now try to match what we found to an entry in our table
	findInstructionByOperands(instruction);

}
