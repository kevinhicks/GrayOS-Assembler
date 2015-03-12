/*
 * instructions.h
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "parser.h"

typedef struct {
	char op[MAX_TOKEN_SIZE];
	int opType;
	int opSize;
	int opSizeExplicitlySet;

} PARAMETER;

typedef struct {
	int ins;
	PARAMETER op[3];
	int bits;
} INSTRUCTION;

//void doInstruction(FILECONTEXT* context);

#define DO_INS_PHASE_COUNT 		0
#define DO_INS_PHASE_ASSEMBLE	1


int doInstruction(ASSEMBLECONTEXT* context, int phase);


#endif /* INSTRUCTIONS_H_ */
