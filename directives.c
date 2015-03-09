/*
 * directives.c
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#include "constants.h"
#include "stdio.h"
#include "string.h"
#include "utils.h"
#include "parser.h"
#include "directives.h"
#include "utils.h"

char directives[200][10] = { "INCLUDE", "DEFINE", "IFDEF", "ENDIF", "BASE",
		"BITS", "\0" };

void doDirective(FILECONTEXT* context) {
	int index = 0;

	readChar(context); //Eat the '#'

	readIdent(context);

	//Create a copy of the directive, we will modify it before comparison later
	char copyOfToken[MAX_TOKEN_SIZE];
	strcpy(copyOfToken, context->tokenBuffer);
	strToUpper(copyOfToken);

	if (strcmp(copyOfToken, "DEFINE") == 0) {
		char defineName[MAX_DEFINE_NAME_SIZE];
		char defineValue[MAX_DEFINE_VALUE_SIZE];

		readIdent(context);
		strcpy(defineName, context->tokenBuffer);

		readLine(context);
		strcpy(defineName, context->tokenBuffer);

	} else {
		skipLine(context);
	}
	index++;

}
