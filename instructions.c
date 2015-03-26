/*
 * instructions.c
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#include "ctype.h"
#include "stdlib.h"

#include "globals.h"
#include "stdio.h"
#include "parser.h"
#include "constants.h"
#include "instructions.h"
#include "opcodes.h"
#include "utils.h"
#include "expressions.h"

#include "string.h"

#include "stdlib.h"

char instructions[][10] = {
		//Basic Instructions
		"AAA", "AAD", "AAM", "AAS", "ADC", "ADD", "AND",
		"CALL", "CBW", "CLC", "CLD", "CLI", "CMC", "CMP", "CMPSB", "CMPSW",
		"CWD", "DAA", "DAS", "DEC", "DIV", "ESC", "HLT", "IDIV", "IMUL", "IN",
		"INC", "INT", "INTO", "IRET", "JCXZ", "JMP", "LAHF", "LDS", "LEA",
		"LES", "LOCK", "LODSB", "LODSW", "LOOP", "LOOPE", "LOOPNE", "LOOPNZ",
		"LOOPZ", "MOV", "MOVSB", "MOVSW", "MUL", "NEG", "NOP", "NOT", "OR",
		"OUT", "POP", "POPF", "PUSH", "PUSHF", "RCL", "RCR", "REP", "REPE",
		"REPNE", "REPNZ", "REPZ", "RET", "RETN", "RETF", "ROL", "ROR", "SAHF",
		"SAL", "SAR", "SBB", "SCASB", "SCASW", "SHL", "SHR", "STC", "STD",
		"STI", "STOSB", "STOSW", "SUB", "TEST", "WAIT", "XCHG", "XLAT", "XOR",
		"JA", "JAE", "JBE", "JBE", "JC", "JE", "JG", "JGE", "JL", "JLE", "JNA",
		"JNAE", "JNB", "JNBE", "JNC", "JNE", "JNG", "JNGE", "JNL", "JNLE",
		"JNO", "JNP", "JNS", "JNZ", "JO", "JP", "JPE", "JPO", "JS", "JZ",

		//Terminator
		"\0" };

INSTRUCTION instruction;

int inFilePos;
int outFilePos;
int lstFilePos;
int preInsAddr;

void memOpDisp(PARAMETER* param) {
	if (param->memOpDesc & (MEMOP_DISP8 | MEMOP_DISP16)) {
		printf("MemOp Disp must be grouped!\n");
	}
	param->memOpDisp = expression();

	//Classify displacement
	if (param->memOpDisp > 127 || param->memOpDisp < -128) {
		param->memOpDesc |= MEMOP_DISP16;
	} else {
		param->memOpDesc |= MEMOP_DISP8;
	}
}
void memOpExpression(PARAMETER* param) {

	param->memOpDesc = 0;
	param->memOpDisp = 0;

	startOfEvaulation:

	//16 BIT MemOp
	if (instruction.addressSize != 32) {
		//Displacement
		if (isdigit(tokens[currTokenIndex][0])) {
			memOpDisp(param);
			return;
		}
		//Base
		else if (!strcmpi("bx", tokens[currTokenIndex])) {
			if (param->memOpDesc & MEMOP_BX) {
				printf("BX used more than once!\n");
				exit(0);
			} else if (param->memOpDesc & MEMOP_BP) {
				printf("Two Base in MemOp!\n");
				exit(0);
			}
			param->memOpDesc |= MEMOP_BX;
			instruction.addressSize = 16;
			currTokenIndex++;

		} else if (!strcmpi("bp", tokens[currTokenIndex])) {
			if (param->memOpDesc & MEMOP_BP) {
				printf("BP used more than once!\n");
				exit(0);
			} else if (param->memOpDesc & MEMOP_BX) {
				printf("Two Base in MemOp!\n");
				exit(0);
			}
			param->memOpDesc |= MEMOP_BP;
			instruction.addressSize = 16;
			currTokenIndex++;
		}
		//Index
		else if (!strcmpi("di", tokens[currTokenIndex])) {
			if (param->memOpDesc & MEMOP_DI) {
				printf("DI used more than once!\n");
				exit(0);
			} else if (param->memOpDesc & MEMOP_SI) {
				printf("Two Index in MemOp!\n");
				exit(0);
			}
			param->memOpDesc |= MEMOP_DI;
			instruction.addressSize = 16;
			currTokenIndex++;

		} else if (!strcmpi("si", tokens[currTokenIndex])) {
			if (param->memOpDesc & MEMOP_SI) {
				printf("SI used more than once!\n");
				exit(0);
			} else if (param->memOpDesc & MEMOP_DI) {
				printf("Two Index in MemOp!\n");
				exit(0);
			}
			param->memOpDesc |= MEMOP_SI;
			instruction.addressSize = 16;
			currTokenIndex++;
		}

		if (tokens[currTokenIndex][0] == '+') {
			currTokenIndex++;
			goto startOfEvaulation;
		} else if (tokens[currTokenIndex][0] == '-') {
			memOpDisp(param);
			return;
		}
	}
	//32 BIT MemOp
	else {

	}

}

void resetInstruction() {
	instruction.byteArrayCount = 0;
	instruction.addressSize = 0;
	instruction.dataSize = 0;

	//Clear params
	int i = 0;
	for (i = 0; i < 3; i++) {
		instruction.parameters[i].memOpDesc = 0;
		instruction.parameters[i].memOpDisp = 0;
		instruction.parameters[i].numberValue = 0;
		instruction.parameters[i].opSize = 0;
		instruction.parameters[i].opSizeExplicitlySet = FALSE;
		instruction.parameters[i].opType = 0;
		instruction.parameters[i].reg = 0;
		instruction.parameters[i].segmentPrefix = 0;
	}
}
//Populate the context.currFile->insDec with the information about this instruction
void doInstruction() {

	resetInstruction();

	instruction.ins = findInstruction(tokens[currTokenIndex]);

	context.foundForwardReference = FALSE;

	if (instruction.ins != INS_NOT_FOUND) {
		currTokenIndex++;

		int param = 0;
		//parse up to 3 params
		for (param = 0; param < 3; param++) {

			//Are we at the end of the line?
			if (tokens[currTokenIndex][0] == '\0') {
				instruction.parameters[param].opType = PARAM_NONE;
				continue;
			}

			//If we are not looking at the first iteration, then there shoudl be a comma here
			if (param > 0) {
				//Eat comma
				if (tokens[currTokenIndex][0] != ',') {
					expect("',' or newline");
				}
				currTokenIndex++;
			}

			//mem op size specifyer
			if (!strcmpi(tokens[currTokenIndex], "byte")) {
				currTokenIndex++;
				instruction.parameters[param].opSize = 8;
			} else if (!strcmpi(tokens[currTokenIndex], "word")) {
				currTokenIndex++;
				instruction.parameters[param].opSize = 16;
			} else if (!strcmpi(tokens[currTokenIndex], "dword")) {
				currTokenIndex++;
				instruction.parameters[param].opSize = 32;
			}

			//MemOp
			if (tokens[currTokenIndex][0] == '[') {
				//Eat '['
				currTokenIndex++;

				instruction.parameters[param].opType = PARAM_MEM;

				memOpExpression(&instruction.parameters[param]);

				//Eat ']'
				if (tokens[currTokenIndex][0] != ']') {
					expect("]");
				}

				currTokenIndex++;

				continue;
			}

			//REG
			int r = isRegister(tokens[currTokenIndex]);
			if (r >= 0) {
				//Segment register?
				int s = isSegRegister(tokens[currTokenIndex]);
				if (s >= 0) {
					instruction.parameters[param].opType = PARAM_SEGREG;
				} else {
					instruction.parameters[param].opType = PARAM_REG;
				}
				instruction.parameters[param].reg = r;

				currTokenIndex++;

				continue;
			}

			//Immediate
			instruction.parameters[param].opType = PARAM_IMM;
			instruction.parameters[param].numberValue = expression();

			currTokenIndex++;
			continue;
			//}

			printf("Unknown operand\n");
			exit(0);
		}

		//Now try to match what we found to an entry in our table
		instruction.opTableEntry = findOpcodeByOperands();
		return;

	} else {
		printf("UNKNOWN INSTRUCTION %s\n", tokens[currTokenIndex]);
	}

	instruction.ins = OP_NOT_FOUND;
	instruction.opTableEntry = NULL;
}

int findInstruction(char* word) {
	int insIndex = 0;

	//Loop thru listing of instructions, and see if we can fine this one
	while (instructions[insIndex][0] != '\0') {
		//If we find it, then return the index
		if (!strcmpi(instructions[insIndex], word)) {
			return insIndex;
		}
		insIndex++;
	}

	//If we never find the instruction, then return INS_NOT_FOUND
	return INS_NOT_FOUND;
}
