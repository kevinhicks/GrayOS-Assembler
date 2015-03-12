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

char directives[][10] = { "INCLUDE",
		"DEFINE",
		"IFDEF",
		"ENDIF",
		"BASE",
		"BITS",
		"DB",
		"DW",
		"DD",
		"DQ",
		"\0" };

int findDirective(char* ident) {

	char copyOfToken[MAX_TOKEN_SIZE];
	strcpy(copyOfToken, ident);

	int index = 0;

	//Look through the list of directive
	//until we find a match, or then end
	//of the list denoted by a '\0'
	while (directives[index][0] != '\0') {
		if (strcmp(copyOfToken, directives[index]) == 0) {
			return index;
		}
		index++;
	}

	return DRTV_NOT_FOUND;
}

void doDirective(int directive, ASSEMBLECONTEXT* context) {
	switch (directive) {
		case DRTV_INCLUDE:
			doInclude(context);
			break;
	}
}

void findAndDoDirective(FILECONTEXT* context) {
	int index = 0;

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

	}
	else if (strcmp(copyOfToken, "DEFINE") == 0) {

	}
	skipLine(context);

	index++;

}

void doInclude(ASSEMBLECONTEXT* context) {
}

