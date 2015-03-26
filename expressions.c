/*
 * expressions.c
 *
 *  Created on: Mar 20, 2015
 *      Author: HICKSK
 */

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stddef.h"
#include "stdlib.h"

#include "globals.h"
#include "expressions.h"
#include "opcodes.h"

int forwardRefFound;

int expression() {
	int t = 0;

	//Unary -/+
	if (tokens[currTokenIndex][0] == '-') {
		currTokenIndex++;
		t -= term();
	} else {
		t = term();
	}

	while (tokens[currTokenIndex][0] == '-' || tokens[currTokenIndex][0] == '+')
	{
		switch (tokens[currTokenIndex][0]) {
			case '+':
				currTokenIndex++;
				t += term();
				break;
			case '-':
				currTokenIndex++;
				t -= term();
				break;
			default:
				expect("Add op");
		}
	}

	return t;
}

int term() {
	int t = factor();
	while (tokens[currTokenIndex][0] == '*' || tokens[currTokenIndex][0] == '/')
	{
		switch (tokens[currTokenIndex][0]) {
			case '*':
				currTokenIndex++;
				t *= factor();
				break;
			case '/':
				currTokenIndex++;
				t /= factor();
				break;
			default:
				expect("Mul op");
		}
	}

	return t;
}

int factor() {
	//Number
	if (isdigit(tokens[currTokenIndex][0])) {
		return strtol(tokens[currTokenIndex++], NULL, 0);
	}
	//Nested expression
	else if (tokens[currTokenIndex][0] == '(') {
		currTokenIndex++;
		int i = expression();
		currTokenIndex++;
		return i;
	}
	//Label
	else {
		if (isRegister(tokens[currTokenIndex]) >= 0) {
			printf("Register in expression!\n");
			exit(0);
		}

		if (labelExists(tokens[currTokenIndex])) {
			if (labelExistsAndPositionDefined(tokens[currTokenIndex])) {
				return getPositionOfLabel(tokens[currTokenIndex++]);
			} else {
				currTokenIndex++;
				forwardRefFound = TRUE;
				return 0;
			}
		} else {
			expect("Factor");

		}
	}
	return 0;
}

