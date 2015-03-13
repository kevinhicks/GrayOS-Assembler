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

void readLineIntoBuffer() {

	context.currFile->lineNumber++;

	int index = 0;
	while (context.currFile->lineBufferLookAhead != '\n' && context.currFile->lineBufferLookAhead != EOF && index < MAX_LINE_BUFFER_SIZE) {
		context.currFile->lineBuffer[index++] = context.currFile->lineBufferLookAhead;

		readCharIntoBuffer();
	}

	context.currFile->lineBuffer[index] = '\0';

	//Check for overflow
	if (index >= MAX_LINE_BUFFER_SIZE && context.currFile->lineBufferLookAhead != '\n') {
		printf("Line: %d exceeds max line length of %d", context.currFile->lineNumber, MAX_LINE_BUFFER_SIZE);
		return;
	}

	if (context.currFile->lineBufferLookAhead != EOF) {
		readCharIntoBuffer(); //Eat newline char
	}

	//reset lookAheadPosition
	context.currFile->lookAheadPosition = 0;
	//Start the buffered pump
	readChar();
}

char readCharIntoBuffer() {
	context.currFile->lineBufferLookAhead = getc(context.currFile->file);

	return context.currFile->lineBufferLookAhead;
}

char* readIdent() {
	int index = 0;

	if (context.currFile->lookAhead == '\0') {
		expect("Identifier");
	}

	//A 'word' must start with a letter
	if (!(isalpha(context.currFile->lookAhead) || context.currFile->lookAhead == '_')) {
		expect("Letter or Underscore");
	}

	while (isalpha(context.currFile->lookAhead) || context.currFile->lookAhead == '_') {
		context.currFile->tokenBuffer[index++] = context.currFile->lookAhead;
		readChar(context);
	}

	context.currFile->tokenBuffer[index++] = '\0';
	context.currFile->charNumber = 1;

	skipWhitespace(context);

	return context.currFile->tokenBuffer;
}

char readChar() {
	if (context.currFile->lookAhead != '\0' || context.currFile->lookAhead != '\n') {
		context.currFile->lookAhead = context.currFile->lineBuffer[context.currFile->lookAheadPosition++];
		context.currFile->charNumber++;

		//Start of a comment, noting else on this line is valid code
		if (context.currFile->lookAhead == ';')
				{
			context.currFile->lookAhead = '\0';
		}

		return context.currFile->lookAhead;
	}
	return '\0';
}

void skipLine() {
	while (context.currFile->lookAhead != EOF && context.currFile->lookAhead != '\n') {
		readChar();
	}

	skipWhitespace();
}

char* readNumber() {
	int index = 0;
	int radix = 10; //default to 10

	//look for 0x or 0b (case insensitive) prefix
	if (context.currFile->lookAhead == '0') {
		readChar();

		//0x
		if (context.currFile->lookAhead == 'x' || context.currFile->lookAhead == 'X') {
			radix = 16;
			readChar();
		}
		//0b
		else if (context.currFile->lookAhead == 'b' || context.currFile->lookAhead == 'B') {
			radix = 8;
			readChar();
		}
	}

	//Fill buffer with digits
	while (isValidHexChar(context.currFile->lookAhead)) {
		context.currFile->tokenBuffer[index++] = context.currFile->lookAhead;
		readChar(context);
	}

	//trailing H
	if (context.currFile->lookAhead == 'h' || context.currFile->lookAhead == 'H') {
		radix = 16;
		readChar(context); //Eat 'h'
	}

	context.currFile->tokenBuffer[index++] = '\0';
	context.currFile->charNumber = 1;
	context.currFile->numberTokenValue = strToInt(context.currFile->tokenBuffer, radix);

	skipWhitespace();

	return context.currFile->tokenBuffer;
}

char* readLine() {
	int index = 0;

	while (context.currFile->lookAhead != EOF && context.currFile->lookAhead != '\n') {
		if (context.currFile->lookAhead == ';') {
			skipLine();
			break;
		}

		context.currFile->tokenBuffer[index++] = context.currFile->lookAhead;

		readChar();
	}

	context.currFile->tokenBuffer[index] = '\0';

	skipWhitespace();

	return context.currFile->tokenBuffer;
}

void skipWhitespace() {
	while (context.currFile->lookAhead == ' ' || context.currFile->lookAhead == '\t') {
		readChar();
	}
}

void skipWhitespaceLines() {
	while ((context.currFile->lookAhead == ' ' || context.currFile->lookAhead == '\t'
			|| context.currFile->lookAhead == '\n') && (context.currFile->lookAhead != EOF)) {
		readChar();
	}
}

void expect(char* expected) {
	printf("Line: %d Char: %d\n%s\nExpected: %s Found: '%c'\n", context.currFile->lineNumber,
			context.currFile->charNumber, context.currFile->lineBuffer, expected, context.currFile->lookAhead);
	exit(0);
}

