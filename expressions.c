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

#include "globals.h"
#include "expressions.h"

forwardRefFound = FALSE;

int expression() {
	int t = 0;

	//Unary -/+
	if (context.currFile->lookAhead == '-')
			{
		readChar();
		t -= term();
	} else {
		t = term();
	}

	while (context.currFile->lookAhead == '-' || context.currFile->lookAhead == '+')
	{
		switch (context.currFile->lookAhead) {
			case '+':
				readChar();
				t += term();
				break;
			case '-':
				readChar();
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
	while (context.currFile->lookAhead == '*' || context.currFile->lookAhead == '/')
	{
		switch (context.currFile->lookAhead) {
			case '*':
				readChar();
				t *= factor();
				break;
			case '/':
				readChar();
				t *= factor();
				break;
			default:
				expect("Mul op");
		}
	}

	return t;
}

int factor() {
	if (isdigit(context.currFile->lookAhead)) {
		int i = getNumber();
		return i;
	} else if (context.currFile->lookAhead == '(') {
		readChar();
		return expression();
		readChar();
	} else {
		readIdent();
		if (labelExists(context.currFile->tokenBuffer)) {
			if (labelExistsAndPositionDefined(context.currFile->tokenBuffer)) {
				return getPositionOfLabel(context.currFile->tokenBuffer);
			} else {

				//Forward ref
				printf("Forward Ref Found: %s\n", context.currFile->tokenBuffer);
				forwardRefFound = TRUE;
			}
		} else {

			//Forward ref
			printf("Forward Ref Found: %s\n", context.currFile->tokenBuffer);
			forwardRefFound = TRUE;
		}
	}
	return 0;
}

int getNumber() {
	readNumber();
	return context.currFile->numberTokenValue;
}
