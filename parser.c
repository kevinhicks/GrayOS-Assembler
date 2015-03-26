/*
 * parser.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "stdio.h"
#include "stdlib.h"

#include "globals.h"
#include "parser.h"
#include "string.h"
#include "ctype.h"
#include "utils.h"
#include "constants.h"

char tokens[100][100];
int currTokenIndex;

void readLineIntoBuffer() {

	context.currFile->lineNumber++;

	//skip empty lines
	while (iswspace(context.currFile->lineBufferLookAhead)) {
		readCharIntoBuffer();
	}

	inFilePos = ftell(context.currFile->file);

	//read in the entire lines
	int index = 0;
	while (context.currFile->lineBufferLookAhead != '\n' && context.currFile->lineBufferLookAhead != EOF && index < MAX_LINE_BUFFER_SIZE) {
		context.currFile->lineBuffer[index++] = context.currFile->lineBufferLookAhead;

		readCharIntoBuffer();
	}

	//terminate line
	context.currFile->lineBuffer[index] = '\0';

	//Check for overflow
	if (index >= MAX_LINE_BUFFER_SIZE && context.currFile->lineBufferLookAhead != '\n') {
		printf("Line: %d exceeds max line length of %d", context.currFile->lineNumber, MAX_LINE_BUFFER_SIZE);
		return;
	}

	//Eat newline char
	if (context.currFile->lineBufferLookAhead != EOF) {
		//readCharIntoBuffer();
	}

	//parse line into tokens
	tokenizeString();
}

void tokenizeString() {
	int inputIndex = 0;
	int tokenIndex = 0;
	int tokenCharIndex = 0;

	currTokenIndex = 0;

	//clear tokens
	for (tokenIndex = 0; tokenIndex < 100; tokenIndex++) {
		tokens[tokenIndex][0] = '\0';
	}
	tokenIndex = 0;

	while (context.currFile->lineBuffer[inputIndex] != '\0')
	{
		tokenCharIndex = 0;
		//Skip all whitespace first
		if (iswspace(context.currFile->lineBuffer[inputIndex])) {
			while (iswspace(context.currFile->lineBuffer[inputIndex])) {
				inputIndex++;
			}
		}

		//If it starts with a character, then assume an identifier, otherwise, it should be a number
		if (isalpha(context.currFile->lineBuffer[inputIndex])) {
			//Multi-char identifier token
			while (isalnum(context.currFile->lineBuffer[inputIndex])) {
				tokens[tokenIndex][tokenCharIndex++] = context.currFile->lineBuffer[inputIndex++];
			}
		}
		//Number?
		else if (isxdigit(context.currFile->lineBuffer[inputIndex])) {
			//Multi-char number token
			while (isalnum(context.currFile->lineBuffer[inputIndex])) {
				tokens[tokenIndex][tokenCharIndex++] = context.currFile->lineBuffer[inputIndex++];
			}
		}
		//String?
		else if(context.currFile->lineBuffer[inputIndex] == '"') {
			tokens[tokenIndex][tokenCharIndex++] = context.currFile->lineBuffer[inputIndex++];
			tokens[tokenIndex][tokenCharIndex++] = '\0';
			tokenIndex++;
			tokenCharIndex = 0;

			while(context.currFile->lineBuffer[inputIndex] != '"') {
				tokens[tokenIndex][tokenCharIndex++] = context.currFile->lineBuffer[inputIndex++];
			}
			tokens[tokenIndex++][tokenCharIndex++] = '\0';

			tokenCharIndex = 0;
			tokens[tokenIndex][tokenCharIndex++] = context.currFile->lineBuffer[inputIndex++];

		}
		//Single-char token?
		else {
			tokens[tokenIndex][tokenCharIndex++] = context.currFile->lineBuffer[inputIndex++];
		}

		tokens[tokenIndex++][tokenCharIndex++] = '\0';
	}

	tokens[tokenIndex][0] = '\0';
}

char readCharIntoBuffer() {
	context.currFile->lineBufferLookAhead = getc(context.currFile->file);

	return context.currFile->lineBufferLookAhead;
}

void expect(char* expected) {
	printf("Line: %d Char: %d\n%s\nExpected: %s Found: ''\n", context.currFile->lineNumber,
			context.currFile->charNumber, context.currFile->lineBuffer, expected);
	exit(0);
}

