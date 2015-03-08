/*
 * instructions.h
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

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

void doInstruction(FILE* file);

#endif /* INSTRUCTIONS_H_ */
