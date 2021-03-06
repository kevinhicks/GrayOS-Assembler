/*
 * main.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stddef.h"
#include "stdlib.h"

#include "parser.h"
#include "constants.h"
#include "opcodes.h"
#include "directives.h"
#include "instructions.h"
#include "assemble.h"
#include "utils.h"
#include "expressions.h"

ASSEMBLECONTEXT context;

int main() {
	char* inputFileName = "testFiles\\test.src";

	FILECONTEXT unifiedFile;
	FILECONTEXT outputFile;
	FILECONTEXT listingFile;

	context.unifiedFile = &unifiedFile;
	context.outputFile = &outputFile;
	context.listingFile = &listingFile;

	beginAssembly();
	assembleFile(inputFileName);
	endAssembly();
	return 0;
}
