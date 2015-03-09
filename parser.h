/*
 * parser.h
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "stdio.h"
#include "constants.h"

char chrLookAhead;
int insideQuotes;

typedef struct {
	FILE* file;
	int lineNumber;
	int charNumber;
	char lookAhead;
	char tokenBuffer[MAX_TOKEN_SIZE];
	char lineBuffer[MAX_LINE_BUFFER];
	int inseideQuotes;
} FILECONTEXT;

char* readIdent(FILECONTEXT* context);
char readChar(FILECONTEXT* context);
char* readLine(FILECONTEXT* context);
char* readNumber(FILECONTEXT* context);

void skipWhitespace(FILECONTEXT* context);
void skipWhitespaceLines(FILECONTEXT* context);
void skipLine(FILECONTEXT* context);

char prefetchChar(FILECONTEXT* context);
void expect(FILECONTEXT* context, char* expected);

#endif /* PARSER_H_ */
