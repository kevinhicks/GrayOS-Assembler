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

PARAMETER classifyNumber(char* buffer) {
	PARAMETER param;

	strcpy(&param.op[0], buffer);

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

void classifyWord(PARAMETER* param, char* buffer) {
	char copyOfWord[MAX_TOKEN_SIZE];

	strcpy(param->op, buffer);
	//another copy. this one will be modifiyed for eaiser comparison
	strcpy(copyOfWord, buffer);
	strToUpper(copyOfWord);

	//Register?

	//Accumulator
	if (!strcmp(copyOfWord, "AL")) {
		param->opType = (OP_AL | OP_REG8 | OP_REG);
	} else if (!strcmp(copyOfWord, "AH")) {
		param->opType = (OP_AH | OP_REG8 | OP_REG);
	} else if (!strcmp(copyOfWord, "AX")) {
		param->opType = (OP_AX | OP_REG16 | OP_REG);
	} else if (!strcmp(copyOfWord, "EAX")) {
		param->opType = (OP_EAX | OP_REG32 | OP_REG);
	}

	//Other 8 bit registers
	else if (!strcmp(copyOfWord, "BL") ||
			!strcmp(copyOfWord, "BH") ||
			!strcmp(copyOfWord, "CL") ||
			!strcmp(copyOfWord, "CH") ||
			!strcmp(copyOfWord, "DL") ||
			!strcmp(copyOfWord, "DH")) {
		param->opType = OP_REG8 | OP_REG;
		param->opSize = 8;
	}

	//Other 16 bit registers
	else if (!strcmp(copyOfWord, "AX") ||
			!strcmp(copyOfWord, "BX") ||
			!strcmp(copyOfWord, "CX") ||
			!strcmp(copyOfWord, "DX")) {
		param->opType = OP_REG16 | OP_REG;
		param->opSize = 16;
	}

	//Other 32 bit registers
	else if (!strcmp(copyOfWord, "EAX") ||
			!strcmp(copyOfWord, "EBX") ||
			!strcmp(copyOfWord, "ECX") ||
			!strcmp(copyOfWord, "EDX")) {
		param->opType = OP_REG32 | OP_REG;
		param->opSize = 32;
	}
}

/*
INSTRUCTION instruction;
 void doInstruction(FILECONTEXT* context) {

 readIdent(context);

 int ins = findInstruction(context.tokenBuffer);

 printf("Instruction: ");
 if (ins == OP_NOT_FOUND) {
 printf("UNKNOWN %s\n", context.tokenBuffer);
 skipLine(context);
 return;
 }

 printf("%s\n", context.tokenBuffer);

 instruction.ins = ins;

 int param = 0;

 //parse up to 3 params
 for (param = 0; param < 3; param++) {

 if (context.lookAhead == '\n' || context.lookAhead == EOF) {
 break;
 }

 if (param > 0) {
 if (context.lookAhead == ',') {
 readChar(context); //Eat comma
 skipWhitespace(context);
 } else {
 expect(context, "',' or newline");
 }
 }

 //Something exists after the instruction
 char op1Buffer[MAX_TOKEN_SIZE];

 if (isdigit(context.lookAhead)) {
 //A Number
 readNumber(context);
 instruction.op[param] = classifyNumber(context.tokenBuffer);
 } else if (isalpha(context.lookAhead) || context.lookAhead == '_') {
 //A DEFINE name
 readIdent(context);
 } else if (context.lookAhead == '[') {
 //A Memory Address Operand
 //These are denoted by square brackets
 readChar(context); //Eat '['
 skipWhitespace(context);

 //A memory address can contain a number, or a identifier
 if (isdigit(context.lookAhead)) {
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
 */

//Populate the context.currFile->insDec with the information about this instruction
void doInstruction() {

	int ins = findInstruction(context.currFile->tokenBuffer);


	context.currFile->insDesc->byteArrayCount = 0;

	printf("Instruction: ");
	if (ins != INS_NOT_FOUND) {

		printf("%s ", context.currFile->tokenBuffer);

		context.currFile->insDesc->ins = ins;

		int param = 0;

		//parse up to 3 params
		for (param = 0; param < 3; param++) {

			//Are we at the end of the line?
			if (context.currFile->lookAhead == '\0') {
				break;
			}

			//If we are not looking at the first iteration, then there shoudl be a comma here
			if (param > 0) {
				if (context.currFile->lookAhead == ',') {
					readChar(); //Eat comma
					skipWhitespace();
				} else {
					expect("',' or newline");
				}
			}

			if (isdigit(context.currFile->lookAhead)) {
				//A Number
				readNumber();
				context.currFile->insDesc->op[param] = classifyNumber(context.currFile->tokenBuffer);
			} else if (isalpha(context.currFile->lookAhead) || context.currFile->lookAhead == '_') {
				//A DEFINE name
				readIdent();
				classifyWord(&context.currFile->insDesc->op[param], context.currFile->tokenBuffer);
			} else if (context.currFile->lookAhead == '[') {
				//A Memory Address Operand
				//These are denoted by square brackets
				readChar(); //Eat '['
				skipWhitespace();

				//A memory address can contain a number, or a identifier
				if (isdigit(context.currFile->lookAhead)) {
					readNumber();
				} else {
					readIdent();
				}

				readChar(); //eat ']'
			}

			skipWhitespace();
		}

		//Now try to match what we found to an entry in our table
		context.currFile->insDesc->opTableEntry = findOpcodeByOperands();
		return;

	} else {
		printf("UNKNOWN INSTRUCTION %s\n", context.currFile->tokenBuffer);
	}

	context.currFile->insDesc->ins = OP_NOT_FOUND;
	context.currFile->insDesc->opTableEntry = NULL;
}

int findInstruction(char* word) {
	char cpyOfWord[MAX_WORD_SIZE];

	//create a copy of the 'word',
	//and upper-case it for later comparison
	strcpy(cpyOfWord, word);
	strToUpper(cpyOfWord);

	int insIndex = 0;

	//Loop thru listing of instructions, and see if we can fine this one
	while (instructions[insIndex][0] != '\0') {
		//If we find it, then return the index
		if (strcmp(instructions[insIndex], cpyOfWord) == 0) {
			return insIndex;
		}
		insIndex++;
	}

	//If we never find the instruction, then return INS_NOT_FOUND
	return INS_NOT_FOUND;
}
