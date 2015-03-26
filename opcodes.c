/*
 * opcodes.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "string.h"
#include "stdio.h"

#include "globals.h"
#include "utils.h"
#include "opcodes.h"
#include "constants.h"
#include "instructions.h"
#include "expressions.h"

//instruction id
//Opcode
//operand 1
//operand 2
int opcodes[][9] = {
		//Basic Instructions
		{ INS_AAA, 0x37, 0x00, 0x00, OP_NONE, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_AAD, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_AAM, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_AAS, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_ADC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_ADD, 0x00, 0x00, 0x00, OP_REG8 | OP_MEM8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_ADD, 0x01, 0x00, 0x00, OP_REG16 | OP_MEM16, OP_REG16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_16BIT | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_ADD, 0x01, 0x00, 0x00, OP_REG32 | OP_MEM32, OP_REG32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_32BIT | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_ADD, 0x04, 0x00, 0x00, OP_AL, OP_IMM8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		/*{ INS_ADD, 0x05, 0x00, 0x00, OP_AX, OP_IMM8 | OP_IMM16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_16BIT, OP_FLAGS_NONE },
		 { INS_ADD, 0x05, 0x00, 0x00, OP_EAX, OP_IMM8 | OP_IMM16 | OP_IMM32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_32BIT, OP_FLAGS_NONE },
		 */
		{ INS_ADD, 0x80, 0x00, 0x00, OP_REG8, OP_IMM8, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM_IMM, OP_FLAGS_NONE },
		{ INS_ADD, 0x83, 0x00, 0x00, OP_REG16, OP_IMM8, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM_IMM | OP_FLAGS_16BIT, OP_FLAGS_NONE },
		{ INS_ADD, 0x83, 0x00, 0x00, OP_REG32, OP_IMM8, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM_IMM | OP_FLAGS_32BIT, OP_FLAGS_NONE },
		{ INS_ADD, 0x81, 0x00, 0x00, OP_REG16, OP_IMM16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM_IMM | OP_FLAGS_16BIT, OP_FLAGS_NONE },
		{ INS_ADD, 0x81, 0x00, 0x00, OP_REG32, OP_IMM32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM_IMM | OP_FLAGS_32BIT, OP_FLAGS_NONE },

		{ INS_AND, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CALL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CBW, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CLC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CLD, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CLI, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CMC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CMP, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CMPSB, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CMPSW, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_CWD, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_DAA, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_DAS, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_DEC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_DIV, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_ESC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_HLT, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_IDIV, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_IMUL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_IN, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_INC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_INT, 0xCD, 0x00, 0x00, OP_IMM8, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_INTO, 0xCE, 0x00, 0x00, OP_NONE, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_IRET, 0xCF, 0x00, 0x00, OP_NONE, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_JCXZ, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_JMP, 0xEB, 0x00, 0x00, OP_DISP8, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JMP, 0xE9, 0x00, 0x00, OP_DISP16, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_16BIT, OP_FLAGS_NONE },
		{ INS_JMP, 0xE9, 0x00, 0x00, OP_DISP32, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_32BIT, OP_FLAGS_NONE },

		{ INS_LAHF, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LDS, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LEA, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LES, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LOCK, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_LODSB, 0xAC, 0x00, 0x00, OP_NONE, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LODSW, 0xAD, 0x00, 0x00, OP_NONE, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_LOOP, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LOOPE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LOOPNE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LOOPNZ, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_LOOPZ, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_MOV, 0x88, 0x00, 0x00, OP_REG8 | OP_MEM8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0x89, 0x00, 0x00, OP_REG16 | OP_MEM16, OP_REG16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_16BIT | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0x89, 0x00, 0x00, OP_REG32 | OP_MEM32, OP_REG32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_32BIT | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0x8A, 0x00, 0x00, OP_REG8, OP_REG8 | OP_MEM8, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0x8B, 0x00, 0x00, OP_REG16, OP_REG16 | OP_MEM16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_16BIT | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0x8B, 0x00, 0x00, OP_REG32, OP_REG32 | OP_MEM32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_32BIT | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0x8C, 0x00, 0x00, OP_REG16 | OP_MEM16, OP_SEGREG, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0x8C, 0x00, 0x00, OP_REG32, OP_SEGREG | OP_MEM32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0x8E, 0x00, 0x00, OP_SEGREG, OP_REG16 | OP_MEM16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_MOV, 0xB0, 0x00, 0x00, OP_REG8, OP_IMM8, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_ADD_REG, OP_FLAGS_NONE },
		{ INS_MOV, 0xB8, 0x00, 0x00, OP_REG16, OP_IMM16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_ADD_REG | OP_FLAGS_16BIT, OP_FLAGS_NONE },
		{ INS_MOV, 0xB8, 0x00, 0x00, OP_REG32, OP_IMM32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_ADD_REG | OP_FLAGS_32BIT, OP_FLAGS_NONE },

		{ INS_MOVSB, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_MOVSW, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_MUL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_NEG, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_NOP, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_NOT, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_OR, 0x0C, 0x00, 0x00, OP_AL, OP_IMM8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_OR, 0x0D, 0x00, 0x00, OP_AX, OP_IMM16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_16BIT, OP_FLAGS_NONE },
		{ INS_OR, 0x0D, 0x00, 0x00, OP_EAX, OP_IMM32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_32BIT, OP_FLAGS_NONE },
		{ INS_OR, 0x08, 0x00, 0x00, OP_REG8 | OP_MEM8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_OR, 0x09, 0x00, 0x00, OP_REG16 | OP_MEM16, OP_REG16, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_16BIT | OP_FLAGS_MODRM, OP_FLAGS_NONE },
		{ INS_OR, 0x09, 0x00, 0x00, OP_REG32 | OP_MEM32, OP_REG32, OP_NONE, OP_FLAGS_OPCODE_COUNT1 | OP_FLAGS_32BIT | OP_FLAGS_MODRM, OP_FLAGS_NONE },

		{ INS_OUT, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_POP, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_POPF, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_PUSH, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_PUSHF, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_RCL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_RCR, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_REP, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_REPE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_REPNE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_REPNZ, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_REPZ, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_RET, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_RETN, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_RETF, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_ROL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_ROR, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SAHF, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SAL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SAR, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SBB, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SCASB, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SCASW, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SHL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SHR, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_STC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_STD, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_STI, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_STOSB, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_STOSW, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_SUB, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_TEST, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_WAIT, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_XCHG, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_XLAT, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_XOR, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JA, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JAE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JBE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JBE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JG, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JGE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JLE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNA, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNAE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNB, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNBE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNC, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNG, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNGE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNL, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNLE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNO, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNP, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNS, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JNZ, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JO, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JP, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JPE, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JPO, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JS, 0x00, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },

		{ INS_JZ, 0x74, 0x00, 0x00, OP_DISP8, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT1, OP_FLAGS_NONE },
		{ INS_JZ, 0x0F, 0x84, 0x00, OP_DISP16, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT2 | OP_FLAGS_16BIT, OP_FLAGS_NONE },
		{ INS_JZ, 0x0F, 0x84, 0x00, OP_DISP32, OP_NONE, OP_NONE, OP_FLAGS_OPCODE_COUNT2 | OP_FLAGS_32BIT, OP_FLAGS_NONE },

		//Terminator
		{ INS_NOT_FOUND, 0x00, 0x00, 0x00, OP_NONE, OP_NONE, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE }
};

char* registersModRM[][4] = {
		{ "AL", "AX", "EAX", "ES" },
		{ "CL", "CX", "ECX", "CS" },
		{ "DL", "DX", "EDX", "SS" },
		{ "BL", "BX", "EBX", "DS" },
		{ "AH", "SP", "SP", "FS" },
		{ "CH", "BP", "BP", "GS" },
		{ "DH", "SI", "SI", "resv" },
		{ "BH", "DI", "DI", "resv" },
		{ "\0", "\0", "\0", "\0" }
};

#define REG_AL		0
#define REG_AH		1
#define REG_AX		2
#define REG_EAX		3
#define REG_CL		4
#define REG_CH		5
#define REG_CX		6
#define REG_ECX		7
#define REG_DL		8
#define REG_DH		9
#define REG_DX		10
#define REG_EDX		11
#define REG_BL		12
#define REG_BH		13
#define REG_BX		14
#define REG_EBX		15
#define REG_SP		16
#define REG_BP		17
#define REG_SI		18
#define REG_DI		19
#define REG_ESP		20
#define REG_EBP		21
#define REG_ESI		22
#define REG_EDI		23
#define REG_CS		24
#define REG_DS		25
#define REG_ES		26
#define REG_FS		27
#define REG_GS		28
#define REG_SS		29

char* registers[] = {
		"AL",
		"AH",
		"AX",
		"EAX",
		"CL",
		"CH",
		"CX",
		"ECX",
		"DL",
		"DH",
		"DX",
		"EDX",
		"BL",
		"BH",
		"BX",
		"EBX",
		"SP",
		"BP",
		"SI",
		"DI",
		"ESP",
		"EBP",
		"ESI",
		"EDI",
		"CS",
		"DS",
		"ES",
		"FS",
		"GS",
		"SS",
		"\0"
};

char getModRMRegFromRegName(char* reg);
int areCompatiableTypes(int availableOperand, PARAMETER* providedOperand);
int regSize(int index) {
	switch (index) {
		case REG_AL:
			case REG_AH:
			case REG_CL:
			case REG_CH:
			case REG_DL:
			case REG_DH:
			case REG_BL:
			case REG_BH:
			return 8;
		case REG_AX:
			case REG_CX:
			case REG_DX:
			case REG_BX:
			case REG_SP:
			case REG_BP:
			case REG_SI:
			case REG_DI:
			case REG_CS:
			case REG_DS:
			case REG_ES:
			case REG_FS:
			case REG_GS:
			case REG_SS:
			return 16;
		case REG_EAX:
			case REG_ECX:
			case REG_EDX:
			case REG_EBX:
			case REG_ESP:
			case REG_EBP:
			case REG_ESI:
			case REG_EDI:
			return 32;
	}

	return 0;
}

int modrm16[][8] = {
		{ MEMOP_BX | MEMOP_SI, MEMOP_BX | MEMOP_DI, MEMOP_BP | MEMOP_SI, MEMOP_BP | MEMOP_DI, MEMOP_SI, MEMOP_DI, MEMOP_DISP16, MEMOP_BX },

		{ MEMOP_BX | MEMOP_SI | MEMOP_DISP8, MEMOP_BX | MEMOP_DI | MEMOP_DISP8, MEMOP_BP | MEMOP_SI | MEMOP_DISP8, MEMOP_BP | MEMOP_DI | MEMOP_DISP8,
		MEMOP_SI | MEMOP_DISP8, MEMOP_DI | MEMOP_DISP8, MEMOP_BP | MEMOP_DISP16, MEMOP_BX | MEMOP_DISP8 },

		{ MEMOP_BX | MEMOP_SI | MEMOP_DISP16, MEMOP_BX | MEMOP_DI | MEMOP_DISP16, MEMOP_BP | MEMOP_SI | MEMOP_DISP16, MEMOP_BP | MEMOP_DI | MEMOP_DISP16,
		MEMOP_SI | MEMOP_DISP16, MEMOP_DI | MEMOP_DISP16, MEMOP_BP | MEMOP_DISP16, MEMOP_BX | MEMOP_DISP16 }
};

unsigned char find16BitModRM(PARAMETER* param) {
	int row = 0;
	int col = 0;

	//todo, fixup for bp. make it look like bp + 0

	for (row = 0; row < 3; row++) {
		for (col = 0; col < 8; col++) {
			if ((param->memOpDesc & modrm16[row][col]) == param->memOpDesc) {
				return (row << 6) + col;
			}
		}
	}

	return -1;
}

//Find the correct version of an opcode by its parameters
int* findOpcodeByOperands() {

	int index = 0;

//Loop thru the entire opcode table, looking for the best possible opcode
	for (index = 0; opcodes[index][OPCODE_FLD_INS] != INS_NOT_FOUND; index++) {
		int* entry = opcodes[index];

		//If this entry is not for our instructions, then move on
		if (entry[OPCODE_FLD_INS] != instruction.ins)
			continue;

		//We have now found a matching instruction, we now need matching params

		//Parameter index
		int param = 0;
		//Watch for invalid parameters
		int invalidParams = FALSE;

		//Look at each parameter
		for (param = 0; param < 3; param++) {

			//Describes what this instruction entry EXPECTS
			int availableOperand = entry[OPCODE_FLD_OPR1 + param];

			//Compares, looking for a fit
			if (!areCompatiableTypes(availableOperand, &instruction.parameters[param])) {
				invalidParams = TRUE;
				break;
			}
		}

		//Did we find a workable entry?
		if (!invalidParams) {
			return entry;
		}
	}

//Did not find any workable entry
	printf("Could not find an opcode to fit the params\n");
	return (int*) OP_NOT_FOUND;
}

int areCompatiableTypes(int availableOperand, PARAMETER* providedOperand) {
	//First check for a missing type/param
	if (availableOperand == OP_NONE && providedOperand->opType == PARAM_NONE) {
		return TRUE;
	}

	//Accumulator
	if ((availableOperand & OP_AL) && providedOperand->opType == PARAM_REG && providedOperand->reg == REG_AL) {
		return TRUE;
	}

	//General Purpose Registers
	if ((availableOperand & OP_REG8) && providedOperand->opType == PARAM_REG && (regSize(providedOperand->reg) == 8)) {
		return TRUE;
	}

	if ((availableOperand & OP_REG16) && providedOperand->opType == PARAM_REG && (regSize(providedOperand->reg) == 16)) {
		return TRUE;
	}

	if ((availableOperand & OP_REG32) && providedOperand->opType == PARAM_REG && (regSize(providedOperand->reg) == 32)) {
		return TRUE;
	}

	//Segment Registers
	if ((availableOperand & OP_SEGREG) && providedOperand->opType == PARAM_SEGREG) {
		return TRUE;
	}

	//Immediate types
	if ((availableOperand & OP_IMM8) && providedOperand->opType == PARAM_IMM) {
		if (providedOperand->numberValue <= 0xFF) {
			return TRUE;
		}
	}

	if ((availableOperand & OP_IMM16) && providedOperand->opType == PARAM_IMM) {
		if (providedOperand->numberValue <= 0xFFFF) {
			return TRUE;
		}
	}

	if ((availableOperand & OP_IMM32) && providedOperand->opType == PARAM_IMM) {
		if (providedOperand->numberValue <= 0xFFFFFFFF) {
			return TRUE;
		}
	}

	//Displacement Types
	if ((availableOperand & OP_DISP8) && providedOperand->opType == PARAM_IMM) {
		return TRUE;
	}

	if ((availableOperand & OP_DISP16) && providedOperand->opType == PARAM_IMM) {
		return TRUE;
	}

	if ((availableOperand & OP_DISP32) && providedOperand->opType == PARAM_IMM) {
		return TRUE;
	}

	//Memory operands
	if ((availableOperand & OP_MEM8) && providedOperand->opType == PARAM_MEM && (providedOperand->opSize == 8)) {
		return TRUE;
	}

	if ((availableOperand & OP_MEM16) && providedOperand->opType == PARAM_MEM && (providedOperand->opSize == 16)) {
		return TRUE;
	}

	if ((availableOperand & OP_MEM32) && providedOperand->opType == PARAM_MEM && (providedOperand->opSize == 32)) {
		return TRUE;
	}

	return FALSE;
}

void populateInstructionBytes() {
	//reset the byte counter
	instruction.byteArrayCount = 0;

	//If we never found a valid entry, then skip out now
	if (instruction.opTableEntry == OP_NOT_FOUND) {
		return;
	}

	//Prefixes
	//Address Size
	if ((instruction.addressSize == 16 && context.bitMode == 32) ||
			(instruction.addressSize == 32 && context.bitMode == 16)) {
		instruction.byteArray[instruction.byteArrayCount++] = OP_PREFIX_BIT_ADDRESS_SIZE_SWITCH;
	}
	//Data size
	if (((instruction.opTableEntry[OPCODE_FLD_FLG1] & OP_FLAGS_16BIT) && context.bitMode == CTX_BITS_32) ||
			((instruction.opTableEntry[OPCODE_FLD_FLG1] & OP_FLAGS_32BIT) && context.bitMode == CTX_BITS_16)) {
		instruction.byteArray[instruction.byteArrayCount++] = OP_PREFIX_BIT_DATA_SIZE_SWITCH;
	}

	//Opcode(s)
	int i = 0;
	//How many opcodes make up the base of this instruction?
	int opCount = (instruction.opTableEntry[OPCODE_FLD_FLG1] & OP_FLAGS_MASK_OPCODE_COUNT) + 1; //Zero based, so increment by 1
	for (i = 0; i < opCount; i++) {
		//Do we add the register to the opcode?
		if (i == 0 && (instruction.opTableEntry[OPCODE_FLD_FLG1] & OP_FLAGS_ADD_REG)) {
			int opc = (unsigned char) instruction.opTableEntry[OPCODE_FLD_OPC1 + i];
			opc += getModRMRegFromRegName(registers[instruction.parameters[0].reg]);
			instruction.byteArray[instruction.byteArrayCount++] = opc;
		} else {
			instruction.byteArray[instruction.byteArrayCount++] = (unsigned char) instruction.opTableEntry[OPCODE_FLD_OPC1 + i];
		}
	}

	//Modifier(s)
	if (instruction.opTableEntry[OPCODE_FLD_FLG1] & OP_FLAGS_MODRM) {
		char mod = 0;
		char reg = 0;
		char rm = 0;

		//Are they both regs?
		if (instruction.parameters[0].opType == PARAM_REG && instruction.parameters[1].opType == PARAM_REG) {

			rm = getModRMRegFromRegName(registers[instruction.parameters[0].reg]);
			reg = getModRMRegFromRegName(registers[instruction.parameters[1].reg]) << 3;

			mod = MODRM_REG_REG | reg | rm;
		}
		else {
			//Reg first?
			if (instruction.parameters[0].opType == PARAM_REG) {
				reg = getModRMRegFromRegName(registers[instruction.parameters[0].reg]);

				//segreg in second?
				if (instruction.parameters[1].opType == PARAM_SEGREG) {
					mod = MODRM_REG_REG;
					reg = getModRMRegFromRegName(registers[instruction.parameters[1].reg]);
				}
				//memop in second?
				else {
					mod = find16BitModRM(&instruction.parameters[1]);
				}
			}
			//Reg second?
			else {
				reg = getModRMRegFromRegName(registers[instruction.parameters[1].reg]);

				//segreg in first?
				if (instruction.parameters[0].opType == PARAM_SEGREG) {
					mod = MODRM_REG_REG;
					reg = getModRMRegFromRegName(registers[instruction.parameters[0].reg]);
				}
				//memop in first
				else {
					mod = find16BitModRM(&instruction.parameters[0]);
				}
			}

			mod = mod | (reg << 3);
		}

		instruction.byteArray[instruction.byteArrayCount++] = mod;
	}
	//MOD R/M for an instruction with an immediate operand is handled slightly different
	else if (instruction.opTableEntry[OPCODE_FLD_FLG1] & OP_FLAGS_MODRM_IMM) {
		int reg = instruction.opTableEntry[OPCODE_FLD_OPC2];
		int mod, rm;

		if (instruction.opTableEntry[OPCODE_FLD_OPR1] & OP_REG_MASK) {
			mod = MODRM_REG_REG;
		}

		rm = getModRMRegFromRegName(registers[instruction.parameters[0].reg]);

		mod = MODRM_REG_REG | reg | rm;
		instruction.byteArray[instruction.byteArrayCount++] = mod;
	}

	//MemOp Displacement
	for (i = 0; i < 3; i++) {
		if (instruction.parameters[i].memOpDesc & MEMOP_DISP8) {
			instruction.byteArray[instruction.byteArrayCount++] = ((char) instruction.parameters[i].memOpDisp);
		} else if (instruction.parameters[i].memOpDesc & MEMOP_DISP16) {
			instruction.byteArray[instruction.byteArrayCount++] = ((short) instruction.parameters[i].memOpDisp);
			instruction.byteArray[instruction.byteArrayCount++] = ((short) (instruction.parameters[i].memOpDisp)) >> 8;
		}
	}

	//Immediate Values Operand 1-3
	for (i = 0; i < 3; i++) {
		int oper = instruction.opTableEntry[OPCODE_FLD_OPR1 + i];
		if (oper & OP_IMM32) {
			instruction.byteArray[instruction.byteArrayCount++] = (instruction.parameters[i].numberValue & 0xFF);
			instruction.byteArray[instruction.byteArrayCount++] = ((instruction.parameters[i].numberValue >> 8) & 0xFF);
			instruction.byteArray[instruction.byteArrayCount++] = ((instruction.parameters[i].numberValue >> 16) & 0xFF);
			instruction.byteArray[instruction.byteArrayCount++] = ((instruction.parameters[i].numberValue >> 24) & 0xFF);
		} else if (oper & OP_IMM16) {
			instruction.byteArray[instruction.byteArrayCount++] = (instruction.parameters[i].numberValue & 0xFF);
			instruction.byteArray[instruction.byteArrayCount++] = ((instruction.parameters[i].numberValue >> 8) & 0xFF);
		} else if (oper & OP_IMM8) {
			instruction.byteArray[instruction.byteArrayCount++] = (instruction.parameters[i].numberValue & 0xFF);
		} else if (oper & OP_DISP8) {
			int offset = context.outputPos + instruction.byteArrayCount;

			if(forwardRefFound) {
				//we found a forward ref, we are guessing anyways. make it a best case senario
				instruction.byteArray[instruction.byteArrayCount++] = 0;
			} else {
				//This is a KNOWN displacement or forward ref
				instruction.byteArray[instruction.byteArrayCount++] = instruction.parameters[i].numberValue - (offset + 1);
			}
		}
	}
}

char getModRMRegFromRegName(char* reg) {
	int r, b;

	for (r = 0; r < 8; r++) {
		for (b = 0; b < 4; b++) {
			if (!strcmpi(reg, registersModRM[r][b])) {
				return r;
			}
		}
	}

	return -1;
}

int isRegister(char* regName) {
	int row = 0;

	//While the first char in the first column is not zero
	while (registers[row][0] != '\0') {
		if (!strcmpi(regName, registers[row])) {
			return row;
		}
		row++;
	}
	return -1;
}

int isSegRegister(char* regName) {
	int r = isRegister(regName);

	if (r >= REG_CS)
		return r;

	return -1;
}
