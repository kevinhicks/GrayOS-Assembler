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

char prefetchChar(FILE* file) {

	char c = getc(file);
	if (c != EOF) {
		ungetc(c, file);
	}

	return c;
}

char* readWord(FILE* file, char* buffer) {

	//char buff[1];
	//fscanf(file, "%c", buff);

	int index = 0;

	//A 'word' must start with a letter
	if ((!isalpha(chrLookAhead) || chrLookAhead == '_') && chrLookAhead != EOF) {
		error("Expected Letter");
	}

	while ((isalpha(chrLookAhead)  || chrLookAhead == '_') && chrLookAhead != EOF) {
		buffer[index++] = chrLookAhead;
		readChar(file);
	}

	buffer[index++] = '\0';
	//printf(buffer);

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
	return chrLookAhead;
}

void skipLine(FILE* file) {
	while (chrLookAhead != EOF && chrLookAhead != '\n') {
		readChar(file);
	}

	skipWhitespace(file);
}

char* readLine(FILE* file, char* buffer) {
	int index = 0;

	while (chrLookAhead != EOF && chrLookAhead != '\n') {
		if(chrLookAhead == ';') {
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
	while ((chrLookAhead == ' ' || chrLookAhead == '\t' || chrLookAhead == '\n')
			&& (chrLookAhead != EOF)) {
		readChar(file);
	}
}
