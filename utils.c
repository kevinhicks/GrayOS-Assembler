/*
 * utils.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "utils.h"
#include "stdio.h"
#include "stdlib.h"

#include "constants.h"

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

int strToInt(char* string, int radix) {
	int index = 0;
	int output = 0;

	while (string[index] != '\0') {
		output *= radix;

		int digitVal = string[index];

		//convert '0'-'9' to 0-9
		digitVal -= '0';

		//convert 'A'-'F' to A-F
		if(digitVal > 10) {
			digitVal = chrToUpper(string[index]);
			digitVal -= ('A' - 10);
		}

		output+= digitVal;

		index++;
	}

	return output;
}

int isValidHexChar(char digit) {
	//look for 0-9
	if (digit >= 48 && digit <= 57) {
		return TRUE;
	}

	digit = chrToUpper(digit);

	//look for A-F
	if (digit >= 65 && digit <= 70) {
		return TRUE;
	}

	return FALSE;
}
