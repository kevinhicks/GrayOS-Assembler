/*
 * parser.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "stdio.h"
#include "stdlib.h"

#include "parser.h"
#include "string.h"
#include "ctype.h"
#include "utils.h"
#include "constants.h"

void readLineIntoBuffer(ASSEMBLECONTEXT* context) {

	context->currFile->lineNumber++;

	int index = 0;
	while (context->currFile->lineBufferLookAhead != '\n' && context->currFile->lineBufferLookAhead != EOF && index < MAX_LINE_BUFFER_SIZE) {
		context->currFile->lineBuffer[index++] = context->currFile->lineBufferLookAhead;

		readCharIntoBuffer(context);
	}

	context->currFile->lineBuffer[index] = '\0';

	//Check for overflow
	if (index >= MAX_LINE_BUFFER_SIZE && context->currFile->lineBufferLookAhead != '\n') {
		printf("Line: %d exceeds max line length of %d", context->currFile->lineNumber, MAX_LINE_BUFFER_SIZE);
		return;
	}

	if (context->currFile->lineBufferLookAhead != EOF) {
		readCharIntoBuffer(context); //Eat newline char
	}

	//reset lookAheadPosition
	context->currFile->lookAheadPosition = 0;
	//Start the buffered pump
	readChar(context);
}

char readCharIntoBuffer(ASSEMBLECONTEXT* context) {
	context->currFile->lineBufferLookAhead = getc(context->currFile->file);

	return context->currFile->lineBufferLookAhead;
}

char* readIdent(ASSEMBLECONTEXT* context) {
	int index = 0;

	if (context->currFile->lookAhead == '\0') {
		expect(context, "Identifier");
	}

	//A 'word' must start with a letter
	if (!(isalpha(context->currFile->lookAhead) || context->currFile->lookAhead == '_')) {
		expect(context, "Letter or Underscore");
	}

	while ((isalpha(context->currFile->lookAhead) || context->currFile->lookAhead == '_')
			&& context->currFile->lookAhead != EOF) {
		context->currFile->tokenBuffer[index++] = context->currFile->lookAhead;
		readChar(context);
	}

	context->currFile->tokenBuffer[index++] = '\0';
	context->currFile->charNumber = 1;

	skipWhitespace(context);

	return context->currFile->tokenBuffer;
}

char readChar(ASSEMBLECONTEXT* context) {
	if (context->currFile->lookAhead != '\0' || context->currFile->lookAhead != '\n') {
		context->currFile->lookAhead = context->currFile->lineBuffer[context->currFile->lookAheadPosition++];
		context->currFile->charNumber++;

		return context->currFile->lookAhead;
	}
	return '\0';
}

void skipLine(ASSEMBLECONTEXT* context) {
	while (context->currFile->lookAhead != EOF && context->currFile->lookAhead != '\n') {
		readChar(context);
	}

	skipWhitespace(context);
}

char* readNumber(ASSEMBLECONTEXT* context) {
	int index = 0;

	//A 'number' must start with a letter
	if (!isdigit(context->currFile->lookAhead) && context->currFile->lookAhead != EOF) {
		expect(context, "Digit");
	}

	while (isdigit(context->currFile->lookAhead) && context->currFile->lookAhead != EOF) {
		context->currFile->tokenBuffer[index++] = context->currFile->lookAhead;
		readChar(context);
	}

	context->currFile->tokenBuffer[index++] = '\0';

	skipWhitespace(context);

	return context->currFile->tokenBuffer;
}

char* readLine(ASSEMBLECONTEXT* context) {
	int index = 0;

	while (context->currFile->lookAhead != EOF && context->currFile->lookAhead != '\n') {
		if (context->currFile->lookAhead == ';') {
			skipLine(context);
			break;
		}

		context->currFile->tokenBuffer[index++] = context->currFile->lookAhead;

		readChar(context);
	}

	context->currFile->tokenBuffer[index] = '\0';

	skipWhitespace(context);

	return context->currFile->tokenBuffer;
}

void skipWhitespace(ASSEMBLECONTEXT* context) {
	while ((context->currFile->lookAhead == ' ' || context->currFile->lookAhead == '\t')
			&& (context->currFile->lookAhead != EOF)) {
		readChar(context);
	}
}

void skipWhitespaceLines(ASSEMBLECONTEXT* context) {
	while ((context->currFile->lookAhead == ' ' || context->currFile->lookAhead == '\t'
			|| context->currFile->lookAhead == '\n') && (context->currFile->lookAhead != EOF)) {
		readChar(context);
	}
}

void expect(ASSEMBLECONTEXT* context, char* expected) {
	printf("Line: %d Char: %d\n%s\nExpected: %s Found: '%c'\n", context->currFile->lineNumber,
			context->currFile->charNumber, context->currFile->lineBuffer, expected, context->currFile->lookAhead);
	exit(0);
}

