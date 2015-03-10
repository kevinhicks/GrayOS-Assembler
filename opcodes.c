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
#include "instructions.h"

//instruction id
//Opcode
//operand 1
//operand 2
int opcodes[][8] = {
		//Basic Instructions
		{ INS_AAA, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_AAD, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_AAM, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_AAS, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_ADC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_ADD, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_AND, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CALL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CBW, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CLC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CLD, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CLI, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CMC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CMP, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CMPSB, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CMPSW, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_CWD, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_DAA, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_DAS, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_DEC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_DIV, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_ESC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_HLT, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_IDIV, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_IMUL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_IN, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_INC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_INT, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_INTO, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_IRET, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JCXZ, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JMP, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LAHF, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LDS, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LEA, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LES, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LOCK, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LODSB, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LODSW, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LOOP, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LOOPE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LOOPNE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LOOPNZ, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_LOOPZ, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_MOV, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_MOVSB, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_MOVSW, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_MUL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_NEG, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_NOP, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_NOT, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_OR, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_OUT, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_POP, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_POPF, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_PUSH, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_PUSHF, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_RCL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_RCR, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_REP, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_REPE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_REPNE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_REPNZ, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_REPZ, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_RET, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_RETN, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_RETF, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_ROL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_ROR, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SAHF, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SAL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SAR, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SBB, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SCASB, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SCASW, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SHL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SHR, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_STC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_STD, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_STI, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_STOSB, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_STOSW, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_SUB, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_TEST, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_WAIT, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_XCHG, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_XLAT, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_XOR, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JA, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JAE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JBE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JBE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JG, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JGE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JLE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNA, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNAE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNB, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNBE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNC, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNG, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNGE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNL, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNLE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNO, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNP, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNS, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JNZ, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JO, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JP, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JPE, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JPO, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JS, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },
		{ INS_JZ, 0x00, 0x00, OP_REG8, OP_REG8, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE },

		//Terminator
		{ INS_NOT_FOUND, 0x00, 0x00, OP_NONE, OP_NONE, OP_NONE, OP_FLAGS_NONE, OP_FLAGS_NONE }
};

/*
 int opcodes[OPCODE_TABLE_SIZE][6] = { { INS_ADD, 0x00, OP_REG8, OP_REG8, 0 }, {
 INS_ADD, 0x00, OP_MEM8, OP_REG8, 0 }, { INS_ADD, 0x02, OP_REG8, OP_REG8, 0 }, {
 INS_ADD, 0x02, OP_REG8, OP_MEM8, 0 }, { INS_ADD, 0x04, OP_IMM16,
 OP_IMM16, 0 } };
 */

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

#define INS_AAA 		100
#define INS_AAD 		101
#define INS_AAM 		102
#define INS_AAS 		103
#define INS_ADC 		104
#define INS_ADD 		105
#define INS_AND 		106
#define INS_CALL 		107
#define INS_CBW 		108
#define INS_CLC 		109
#define INS_CLD 		110
#define INS_CLI 		111
#define INS_CMC 		112
#define INS_CMP 		113
#define INS_CMPSB 		114
#define INS_CMPSW 		115
#define INS_CWD 		116
#define INS_DAA 		117
#define INS_DAS 		118
#define INS_DEC 		119
#define INS_DIV		 	120
#define INS_ESC		 	121
#define INS_HLT		 	122
#define INS_IDIV 		123
#define INS_IMUL 		124
#define INS_IN 			125
#define INS_INC 		126
#define INS_INT 		127
#define INS_INTO		128
#define INS_IRET 		129
#define INS_JCXZ 		130
#define INS_JMP 		131
#define INS_LAHF 		132
#define INS_LDS 		133
#define INS_LEA 		134
#define INS_LES 		135
#define INS_LOCK 		136
#define INS_LODSB 		137
#define INS_LODSW	 	138
#define INS_LOOP 		139
#define INS_LOOPE 		140
#define INS_LOOPNE 		141
#define INS_LOOPNZ 		142
#define INS_LOOPZ 		143
#define INS_MOV			144
#define INS_MOVSB 		145
#define INS_MOVSW 		146
#define INS_MUL 		147
#define INS_NEG		 	148
#define INS_NOP 		149
#define INS_NOT 		150
#define INS_OR	 		151
#define INS_OUT 		152
#define INS_POP 		153
#define INS_POPF	 	154
#define INS_PUSH 		155
#define INS_PUSHF 		156
#define INS_RCL 		157
#define INS_RCR 		158
#define INS_REP 		159
#define INS_REPE 		160
#define INS_REPNE 		161
#define INS_REPNZ 		162
#define INS_REPZ 		163
#define INS_RET 		164
#define INS_RETN 		165
#define INS_RETF 		166
#define INS_ROL 		167
#define INS_ROR 		168
#define INS_SAHF 		169
#define INS_SAL 		170
#define INS_SAR 		171
#define INS_SBB 		172
#define INS_SCASB 		173
#define INS_SCASW 		174
#define INS_SHL 		175
#define INS_SHR 		176
#define INS_STC 		177
#define INS_STD 		178
#define INS_STI 		179
#define INS_STOSB 		180
#define INS_STOSW 		181
#define INS_SUB 		182
#define INS_TEST 		183
#define INS_WAIT 		184
#define INS_XCHG 		185
#define INS_XLAT 		186
#define INS_XOR 		187
#define INS_JA 			188
#define INS_JAE 		189
#define INS_JB	 		190
#define INS_JBE 		191
#define INS_JC 			192
#define INS_JE 			193
#define INS_JG 			194
#define INS_JGE 		195
#define INS_JL 			196
#define INS_JLE 		197
#define INS_JNA 		198
#define INS_JNAE		199
#define INS_JNB 		200
#define INS_JNBE 		201
#define INS_JNC 		202
#define INS_JNE 		203
#define INS_JNG 		204
#define INS_JNGE 		205
#define INS_JNL 		206
#define INS_JNLE 		207
#define INS_JNO 		208
#define INS_JNP 		209
#define INS_JNS 		210
#define INS_JNZ 		211
#define INS_JO 			212
#define INS_JP 			213
#define INS_JPE 		214
#define INS_JPO 		215
#define INS_JS 			216
#define INS_JZ 			217

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
int* findInstructionByOperands(INSTRUCTION ins) {

	int index = 0;

	//Loop thru the entire opcode table, looking for the best possible opcode
	for (index = 0; index < OPCODE_TABLE_SIZE; index++) {
		int* entry = opcodes[index];

		//If this entry is not for our instructions, then move on
		if (!entry[0] == ins.ins)
			continue;

		//compare params
		int param = 0;
		for (param = 0; param < 3; param++) {
			if (entry[param + 2] == 0) {
				continue;
			}

			if (areCompatiableTypes(entry[param + 2],
					ins.op[param].opType) == TRUE) {
				printf("FOUND A WINNER!\n");
			}
		}

	}

	//Did not find any workable entry
	return (int*) INS_NOT_FOUND;
}

int areCompatiableTypes(int availableOperand, int providedOperand) {
	if (availableOperand == OP_IMM8) {
		if (providedOperand == OP_IMM8) {
			return TRUE;
		}
	}

	if (availableOperand == OP_IMM16) {
		if (providedOperand == OP_IMM8 || providedOperand == OP_IMM16) {
			return TRUE;
		}
	}

	if (availableOperand == OP_IMM32) {
		if (providedOperand == OP_IMM8 || providedOperand == OP_IMM16
				|| providedOperand == OP_IMM32) {
			return TRUE;
		}
	}

	return FALSE;
}
