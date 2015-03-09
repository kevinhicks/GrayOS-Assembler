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

char* readIdent(FILECONTEXT* context) {
	int index = 0;

		//A 'word' must start with a letter
		if ((!isalpha(context->lookAhead) || context->lookAhead == '_') && context->lookAhead != EOF) {
			expect(context, "Letter");
		}

		while ((isalpha(context->lookAhead) || context->lookAhead == '_') && context->lookAhead != EOF) {
			context->tokenBuffer[index++] = context->lookAhead;
			readChar(context);
		}

		context->tokenBuffer[index++] = '\0';

		skipWhitespace(context);

		return context->tokenBuffer;
}

char readChar(FILECONTEXT* context) {
	if(context->lookAhead == '\n') {
		context->lineNumber++;
		context->charNumber = 0;
	}

	context->lookAhead = getc(context->file);


	if (insideQuotes == FALSE) {
		if (context->lookAhead == ';') {
			skipLine(context);
		}
	}
	context->charNumber++;
	return context->lookAhead;
}

void skipLine(FILECONTEXT* context) {
	while (context->lookAhead != EOF && context->lookAhead != '\n') {
		readChar(context);
	}

	skipWhitespace(context);
}

char* readNumber(FILECONTEXT* context) {
	int index = 0;

	//A 'number' must start with a letter
	if (!isdigit(context->lookAhead) && context->lookAhead != EOF) {
		expect(context, "Digit");
	}

	while (isdigit(context->lookAhead) && context->lookAhead != EOF) {
		context->tokenBuffer[index++] = context->lookAhead;
		readChar(context);
	}

	context->tokenBuffer[index++] = '\0';

	skipWhitespace(context);

	return context->tokenBuffer;
}

char* readLine(FILECONTEXT* context) {
	int index = 0;

	while (context->lookAhead != EOF && context->lookAhead != '\n') {
		if (context->lookAhead == ';') {
			skipLine(context);
			break;
		}

		context->tokenBuffer[index++] = context->lookAhead;

		readChar(context);
	}

	context->tokenBuffer[index] = '\0';

	skipWhitespace(context);

	return context->tokenBuffer;
}

void skipWhitespace(FILECONTEXT* context) {
	while ((context->lookAhead == ' ' || context->lookAhead == '\t')
			&& (context->lookAhead != EOF)) {
		readChar(context);
	}
}

void skipWhitespaceLines(FILECONTEXT* context) {
	while ((context->lookAhead == ' ' || context->lookAhead == '\t' || context->lookAhead == '\n')
			&& (context->lookAhead != EOF)) {
		readChar(context);
	}
}


void expect(FILECONTEXT* context, char* expected) {
	printf("Line: %d Char: %d Expected: %s Found: '%c'\n", context->lineNumber, context->charNumber, expected, context->lookAhead);
	exit(0);
}

