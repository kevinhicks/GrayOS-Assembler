/*
 * utils.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "utils.h"
#include "stdio.h"

char* lowers = "abcdefghijklmnopqrstuvwxyz";
char* uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//Convert a string to all Upper case letters
char* strToUpper(char* string) {
	int index = 0;

	while (string[index] != 0) {
		string[index] = chrToUpper(string[index]);
		index++;
	}

	return string;
}

//Convert a string to all Lower case letters
char* strTolower(char* string) {
	int index = 0;

	while (string[index] != 0) {
		string[index] = chrToLower(string[index]);
	}

	return string;
}

//Convert a single character to its upper-case equivalent
char chrToUpper(char letter) {
	int i = 0;
	for (i = 0; i < 26; i++) {
		if (letter == lowers[i]) {
			return uppers[i];
		}
	}

	return letter;
}

//Convert a single character to its lower-case equivalent
char chrToLower(char letter) {
	int i = 0;
	for (i = 0; i < 26; i++) {
		if (letter == uppers[i]) {
			return lowers[i];
		}
	}

	return letter;
}

void error(char* message) {
	printf("\n**%s**\n", message);
	exit(0);
}
