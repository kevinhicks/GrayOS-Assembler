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
	char tokenBuffer[MAX_TOKEN_SIZE];
	char lineBuffer[MAX_LINE_BUFFER];
} AssemblerFile;

char* readWord(FILE* file, char* buffer);
char* readIdent(FILE* file, char* buffer);
char readChar(FILE* file);
char* readLine(FILE* file, char* buffer);
char* readNumber(FILE* file, char* buffer);

void skipWhitespace(FILE* file);
void skipWhitespaceLines(FILE* file);
void skipLine(FILE* file);

char prefetchChar(FILE* file);
void expect(char expected);

#endif /* PARSER_H_ */
