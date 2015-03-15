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
#include "globals.h"

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

int directivesTable[][2] = {
		{ DRTV_INCLUDE, DRTV_PHASE0 },
		{ DRTV_DEFINE, DRTV_PHASE1 },
		{ DRTV_IFDEF, DRTV_PHASE0 | DRTV_PHASE1 | DRTV_PHASE2 },
		{ DRTV_ENDIF, DRTV_PHASE0 | DRTV_PHASE1 | DRTV_PHASE2 },
		{ DRTV_BASE, DRTV_PHASE1 },
		{ DRTV_BITS, DRTV_PHASE1 | DRTV_PHASE2 },
		{ DRTV_DB, DRTV_PHASE1 | DRTV_PHASE2 },
		{ DRTV_DW, DRTV_PHASE1 | DRTV_PHASE2 },
		{ DRTV_DD, DRTV_PHASE1 | DRTV_PHASE2 },
		{ DRTV_DQ, DRTV_PHASE1 | DRTV_PHASE2 },
		{ DRTV_NOT_FOUND, 0 }
};

int findDirective(char* ident, int phase) {

	char copyOfToken[MAX_TOKEN_SIZE];
	strcpy(copyOfToken, ident);
	strToUpper(copyOfToken);

	int index = 0;

	//Look through the list of directive
	//until we find a match, or then end
	//of the list denoted by a '\0'
	while (directives[index][0] != '\0') {
		//Does the name match
		if (strcmp(copyOfToken, directives[index]) == 0) {
			//Is it for the correct phase
			if ((directivesTable[index][1] & phase))
				return index;
		}
		index++;
	}

	return DRTV_NOT_FOUND;
}
/*
 void doDirective(int directive) {
 switch (directive) {
 case DRTV_INCLUDE:
 doInclude();
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
 */
void doDeclareBytes(int size) {
	INSTRUCTION* ins = context.currFile->insDesc;

	startOfByte:

	//a string
	if (context.currFile->lookAhead == '\'') {
		readChar();
		while (context.currFile->lookAhead != '\'') {
			if (context.currFile->lookAhead == '\0') {
				expect("'");
			}

			if (ins->byteArrayCount == 1024) {
				expect("End of line");
			}

			ins->byteArray[ins->byteArrayCount++] = context.currFile->lookAhead;

			readChar();
		}
		readChar(); //eat '
	} else {
		readNumber();

		switch (size) {
			case 1:
				if (context.currFile->numberTokenValue > 0xFF) {
					expect("Number 0-255");
				}
				ins->byteArray[ins->byteArrayCount++] = context.currFile->numberTokenValue & 0xFF;
				break;

			case 2:
				if (context.currFile->numberTokenValue > 0xFFFF) {
					expect("Number 0-0xFFFF");
				}
				ins->byteArray[ins->byteArrayCount++] = context.currFile->numberTokenValue & 0xFF;
				ins->byteArray[ins->byteArrayCount++] = (context.currFile->numberTokenValue >> 8) & 0xFF;
				break;

			case 4:
				ins->byteArray[ins->byteArrayCount++] = context.currFile->numberTokenValue & 0xFF;
				ins->byteArray[ins->byteArrayCount++] = (context.currFile->numberTokenValue >> 8) & 0xFF;
				ins->byteArray[ins->byteArrayCount++] = (context.currFile->numberTokenValue >> 16) & 0xFF;
				ins->byteArray[ins->byteArrayCount++] = (context.currFile->numberTokenValue >> 24) & 0xFF;
				break;

		}
	}

	skipWhitespace();

	if (context.currFile->lookAhead == ',') {
		readChar(); //eat ,
		skipWhitespace();

		goto startOfByte;
	}
}
