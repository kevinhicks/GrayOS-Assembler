/*
 * opcodes.h
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#ifndef OPCODES_H_
#define OPCODES_H_

#include "constants.h"
#include "instructions.h"

#define INS_NOT_FOUND	0
#define INS_AAA 		100
#define INS_ADD 		101

#define OP_NOT_FOUND 0
#define OP_REG		0x01
#define OP_REG8 	0x02
#define OP_REG16 	0x04
#define OP_REG32 	0x08
#define OP_MEM 		0x10
#define OP_MEM8 	0x20
#define OP_MEM16 	0x40
#define OP_MEM32 	0x80
#define OP_IMM 		0x100
#define OP_IMM8 	0x200
#define OP_IMM16	0x400
#define OP_IMM32 	0x800

#define OP_SIZE_8	8
#define OP_SIZE_16	16
#define OP_SIZE_32	32

int findInstruction(char* word);
int* findInstructionByOperands(INSTRUCTION ins);

int areCompatiableTypes(int availableOperand, int providedOperand);
#endif /* OPCODES_H_ */
