/*
 * parser.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "stdio.h"
#include "parser.h"
#include "string.h"
#include "ctype.h"
#include "utils.h"
#include "constants.h"

char* readWord(FILE* file, char* buffer) {
	int index = 0;

	//A 'word' must start with a letter
	if ((!isalpha(chrLookAhead) || chrLookAhead == '_') && chrLookAhead != EOF) {
		error("Expected Letter");
	}

	while ((isalpha(chrLookAhead) || chrLookAhead == '_') && chrLookAhead != EOF) {
		buffer[index++] = chrLookAhead;
		readChar(file);
	}

	buffer[index++] = '\0';

	skipWhitespace(file);

	return buffer;
}

char* readIdent(FILE* file, char* buffer) {
	return readWord(file, buffer);
}

void expect(char expected) {

}

char readChar(FILE* file) {
	chrLookAhead = getc(file);

	if (insideQuotes == FALSE) {
		if (chrLookAhead == ';') {
			skipLine(file);
		}
	}
	return chrLookAhead;
}

char readChar2(FILECONTEXT* context) {
	chrLookAhead = getc(context->file);

	if (insideQuotes == FALSE) {
		if (chrLookAhead == ';') {
			skipLine(context);
		}
	}
	return chrLookAhead;
}

void skipLine(FILE* file) {
	while (chrLookAhead != EOF && chrLookAhead != '\n') {
		readChar(file);
	}

	skipWhitespace(file);
}

char* readNumber(FILE* file, char* buffer) {
	int index = 0;

	//A 'number' must start with a letter
	if (!isdigit(chrLookAhead) && chrLookAhead != EOF) {
		error("Expected Digit");
	}

	while (isdigit(chrLookAhead) && chrLookAhead != EOF) {
		buffer[index++] = chrLookAhead;
		readChar(file);
	}

	buffer[index++] = '\0';

	skipWhitespace(file);

	return buffer;
}

char* readLine(FILE* file, char* buffer) {
	int index = 0;

	while (chrLookAhead != EOF && chrLookAhead != '\n') {
		if (chrLookAhead == ';') {
			skipLine(file);
			break;
		}

		buffer[index++] = chrLookAhead;

		readChar(file);
	}

	buffer[index] = '\0';

	skipWhitespace(file);

	return buffer;
}

void skipWhitespace(FILE* file) {
	while ((chrLookAhead == ' ' || chrLookAhead == '\t')
			&& (chrLookAhead != EOF)) {
		readChar(file);
	}
}

void skipWhitespaceLines(FILE* file) {
	while ((chrLookAhead == ' ' || chrLookAhead == '\t' || chrLookAhead == '\n')
			&& (chrLookAhead != EOF)) {
		readChar(file);
	}
}
