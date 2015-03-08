/*
 * instructions.c
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#include "stdio.h"
#include "parser.h"
#include "constants.h"
#include "instructions.h"
#include "opcodes.h"

void doInstruction(FILE* file) {

	char buffer[MAX_TOKEN_SIZE];

	readWord(file, buffer);
	printf("Word: %s\n", buffer);
}
