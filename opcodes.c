/*
 * opcodes.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "string.h"
#include "stdio.h"
#include "utils.h"
#include "opcodes.h"
#include "constants.h"

//instruction id
//Opcode
//operand 1
//operand 2
int opcodes[OPCODE_TABLE_SIZE][6] = {
		{ INS_ADD, 0x00, OP_REG8, OP_REG8, 0 },
		{ INS_ADD, 0x00, OP_MEM8, OP_REG8, 0 },
		{ INS_ADD, 0x02, OP_REG8, OP_REG8, 0 },
		{ INS_ADD, 0x02, OP_REG8, OP_MEM8, 0 } };

char instructions[300][10] = { "AAA", "ADD", "\0" };

int findInstruction(char* word) {
	char cpyOfWord[MAX_WORD_SIZE];

	//create a copy of the 'word',
	//and upper-case it for later comparison
	strcpy(cpyOfWord, word);
	strToUpper(cpyOfWord);

	int insIndex = 0;

	//Loop thru listing of instructions, and see if we can fine this one
	for (insIndex = 0; insIndex < 300; insIndex++) {
		//If we find it, then return the index
		if (strcmp(instructions[insIndex], cpyOfWord) == 0) {
			return insIndex;
		}
	}

	//If we never find the instruction, then return OP_NOT_FOUND
	return OP_NOT_FOUND;
}

//Find the correct version of an instruction by its parameters
int* findInstructionByOperands(int ins, int op1, int op2, int op3) {

	int index = 0;

	//Loop thru the entire opcode table, looking for the best possible opcode
	for (index = 0; index < OPCODE_TABLE_SIZE; index++) {
		int* entry = opcodes[index];

		//If this entry is not for our instructions, then move on
		if (!entry[0] == ins)
			continue;

	}

	//Did not find any workable entry
	return (int*) INS_NOT_FOUND;
}
