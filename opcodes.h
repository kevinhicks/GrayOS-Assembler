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

#define OP_NOT_FOUND 0
#define OP_NONE		0
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

//The columns in the opcode table
#define OPCODE_FLD_INS	0	//Instruction
#define OPCODE_FLD_OPC1	1	//Opcode 1
#define OPCODE_FLD_OPC2	2	//Opcode 2
#define OPCODE_FLD_OPC3	3	//Opcode 2
#define OPCODE_FLD_OPR1	4	//Operand 1
#define OPCODE_FLD_OPR2	5	//Operand 2
#define OPCODE_FLD_OPR3	6	//Operand 3
#define OPCODE_FLD_FLG1	7	//Flag 1
#define OPCODE_FLD_FLG2	8	//Flag 2

//Flags that describe each opcode
#define OP_FLAGS_NONE			0
#define OP_FLAGS_OPCODE_COUNT1	0	//instruction has 1 opcode
#define OP_FLAGS_OPCODE_COUNT2	1	//instruction has 2 opcode
#define OP_FLAGS_OPCODE_COUNT3	2	//instruction has 3 opcode
#define OP_FLAGS_16BIT			4	//instruction is for 16bit
#define OP_FLAGS_32BIT			8	//instruction is for 32bit
#define OP_FLAGS_MODRM			16	//instruction has the 1 mod r/m byte
#define OP_FLAGS_ADD_REG		32	//instruction opcode includes register selector

//3 bit register selector. Added to the opcode of some instructions like "mov al, imm8"
#define OP_REG_SEL_AL			0
#define OP_REG_SEL_CL			1
#define OP_REG_SEL_DL			2
#define OP_REG_SEL_BL			3
#define OP_REG_SEL_AH			4
#define OP_REG_SEL_CH			5
#define OP_REG_SEL_DH			6
#define OP_REG_SEL_BH			7

#define OP_REG_SEL_AX			0
#define OP_REG_SEL_CX			1
#define OP_REG_SEL_DX			2
#define OP_REG_SEL_BX			3
#define OP_REG_SEL_SP			4
#define OP_REG_SEL_BP			5
#define OP_REG_SEL_SI			6
#define OP_REG_SEL_DI			7

#define OP_REG_SEL_EAX			0
#define OP_REG_SEL_ECX			1
#define OP_REG_SEL_EDX			2
#define OP_REG_SEL_EBX			3
#define OP_REG_SEL_ESP			4
#define OP_REG_SEL_EBP			5
#define OP_REG_SEL_ESI			6
#define OP_REG_SEL_EDI			7


//Mask used to find parts of the field
#define OP_FLAGS_MASK_OPCODE_COUNT (OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_OPCODE_COUNT2 | OP_FLAGS_OPCODE_COUNT3)

#define OP_SIZE_8	8
#define OP_SIZE_16	16
#define OP_SIZE_32	32

int* findOpcodeByOperands(INSTRUCTION ins);
int countOpcodeBytes();

int areCompatiableTypes(int availableOperand, int providedOperand);
#endif /* OPCODES_H_ */
