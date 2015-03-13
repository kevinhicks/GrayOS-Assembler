/*
 * instructions.h
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "parser.h"
#include "assemble.h"


#define INS_NOT_FOUND	-1
#define INS_AAA 		0
#define INS_AAD 		1
#define INS_AAM 		2
#define INS_AAS 		3
#define INS_ADC 		4
#define INS_ADD 		5
#define INS_AND 		6
#define INS_CALL 		7
#define INS_CBW 		8
#define INS_CLC 		9
#define INS_CLD 		10
#define INS_CLI 		11
#define INS_CMC 		12
#define INS_CMP 		13
#define INS_CMPSB 		14
#define INS_CMPSW 		15
#define INS_CWD 		16
#define INS_DAA 		17
#define INS_DAS 		18
#define INS_DEC 		19
#define INS_DIV		 	20
#define INS_ESC		 	21
#define INS_HLT		 	22
#define INS_IDIV 		23
#define INS_IMUL 		24
#define INS_IN 			25
#define INS_INC 		26
#define INS_INT 		27
#define INS_INTO		28
#define INS_IRET 		29
#define INS_JCXZ 		30
#define INS_JMP 		31
#define INS_LAHF 		32
#define INS_LDS 		33
#define INS_LEA 		34
#define INS_LES 		35
#define INS_LOCK 		36
#define INS_LODSB 		37
#define INS_LODSW	 	38
#define INS_LOOP 		39
#define INS_LOOPE 		40
#define INS_LOOPNE 		41
#define INS_LOOPNZ 		42
#define INS_LOOPZ 		43
#define INS_MOV			44
#define INS_MOVSB 		45
#define INS_MOVSW 		46
#define INS_MUL 		47
#define INS_NEG		 	48
#define INS_NOP 		49
#define INS_NOT 		50
#define INS_OR	 		51
#define INS_OUT 		52
#define INS_POP 		53
#define INS_POPF	 	54
#define INS_PUSH 		55
#define INS_PUSHF 		56
#define INS_RCL 		57
#define INS_RCR 		58
#define INS_REP 		59
#define INS_REPE 		60
#define INS_REPNE 		61
#define INS_REPNZ 		62
#define INS_REPZ 		63
#define INS_RET 		64
#define INS_RETN 		65
#define INS_RETF 		66
#define INS_ROL 		67
#define INS_ROR 		68
#define INS_SAHF 		69
#define INS_SAL 		70
#define INS_SAR 		71
#define INS_SBB 		72
#define INS_SCASB 		73
#define INS_SCASW 		74
#define INS_SHL 		75
#define INS_SHR 		76
#define INS_STC 		77
#define INS_STD 		78
#define INS_STI 		79
#define INS_STOSB 		80
#define INS_STOSW 		81
#define INS_SUB 		82
#define INS_TEST 		83
#define INS_WAIT 		84
#define INS_XCHG 		85
#define INS_XLAT 		86
#define INS_XOR 		87
#define INS_JA 			88
#define INS_JAE 		89
#define INS_JB	 		90
#define INS_JBE 		91
#define INS_JC 			92
#define INS_JE 			93
#define INS_JG 			94
#define INS_JGE 		95
#define INS_JL 			96
#define INS_JLE 		97
#define INS_JNA 		98
#define INS_JNAE		99
#define INS_JNB 		100
#define INS_JNBE 		101
#define INS_JNC 		102
#define INS_JNE 		103
#define INS_JNG 		104
#define INS_JNGE 		105
#define INS_JNL 		106
#define INS_JNLE 		107
#define INS_JNO 		108
#define INS_JNP 		109
#define INS_JNS 		110
#define INS_JNZ 		111
#define INS_JO 			112
#define INS_JP 			113
#define INS_JPE 		114
#define INS_JPO 		115
#define INS_JS 			116
#define INS_JZ 			117


typedef struct {
	char op[MAX_TOKEN_SIZE];
	int opType;
	int opSize;
	int opSizeExplicitlySet;

} PARAMETER;

typedef struct {
	int ins;			//The ID of the instruction
	int* opTableEntry;	//Pointer to the entry in the opcode table that best matches this instruction
	PARAMETER op[3];
	int bits;
} INSTRUCTION;

//void doInstruction(FILECONTEXT* context);

#define DO_INS_PHASE_COUNT 		0
#define DO_INS_PHASE_ASSEMBLE	1


void doInstruction();

int findInstruction(char* word);

#endif /* INSTRUCTIONS_H_ */
