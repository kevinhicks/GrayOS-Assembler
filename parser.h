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

void init();

char* readIdent();
char readChar();
char* readLine();
char* readNumber();

void skipWhitespace();
void skipWhitespaceLines();
void skipLine();

char prefetchChar();
void expect(char* expected);

void readLineIntoBuffer();
char readCharIntoBuffer();

#endif /* PARSER_H_ */
