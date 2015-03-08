/*
 * directives.c
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#include "constants.h"
#include "stdio.h"
#include "string.h"
#include "utils.h"
#include "parser.h"
#include "directives.h"

char directives[200][10] = { "INCLUDE", "DEFINE", "IFDEF", "ENDIF", "BASE",
		"BITS", "\0" };

void doDirective(FILE* file) {
	int index = 0;

	readChar(file); //Eat the '#'

	char buffer[MAX_TOKEN_SIZE];

	readWord(file, buffer);

	strToUpper(buffer);

	printf("Directive: ");

	if (strcmp(buffer, "DEFINE") == 0) {
		char defineName[MAX_DEFINE_NAME_SIZE];
		char defineValue[MAX_DEFINE_VALUE_SIZE];

		readIdent(file, defineName);
		readLine(file, defineValue);


		printf("DEFINE\n\tNAME: %s\n\tVALUE: %s\n", defineName, defineValue);
	} else {
		printf("UNKNOWN!");
		skipLine(file);
	}
	index++;

}
