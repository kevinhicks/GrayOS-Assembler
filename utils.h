/*
 * utils.h
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#ifndef UTILS_H_
#define UTILS_H_

char* strToUpper(char* string);
char* strTolower(char* string);

char chrToUpper(char letter);
char chrToLower(char letter);

void error(char* message);

int isValidHexChar(char digit);

int strToInt(char* string, int radix);

typedef int bool;

#endif /* UTILS_H_ */
