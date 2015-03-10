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

#define OP_FLAGS_NONE	0

#define OP_SIZE_8	8
#define OP_SIZE_16	16
#define OP_SIZE_32	32

int findInstruction(char* word);
int* findInstructionByOperands(INSTRUCTION ins);

int areCompatiableTypes(int availableOperand, int providedOperand);
#endif /* OPCODES_H_ */
