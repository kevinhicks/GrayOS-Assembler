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
#include "assemble.h"

char chrLookAhead;
int insideQuotes;

void init(ASSEMBLECONTEXT* assembleContext);

char* readIdent(ASSEMBLECONTEXT* context);
char readChar(ASSEMBLECONTEXT* context);
char* readLine(ASSEMBLECONTEXT* context);
char* readNumber(ASSEMBLECONTEXT* context);

void skipWhitespace(ASSEMBLECONTEXT* context);
void skipWhitespaceLines(ASSEMBLECONTEXT* context);
void skipLine(ASSEMBLECONTEXT* context);

char prefetchChar(ASSEMBLECONTEXT* context);
void expect(ASSEMBLECONTEXT* context, char* expected);

void readLineIntoBuffer(ASSEMBLECONTEXT* context);
char readCharIntoBuffer(ASSEMBLECONTEXT* context);

#endif /* PARSER_H_ */
