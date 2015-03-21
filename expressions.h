/*
 * expressions.h
 *
 *  Created on: Mar 20, 2015
 *      Author: HICKSK
 */

#ifndef EXPRESSIONS_H_
#define EXPRESSIONS_H_

int expression();
int getNumber();
int term();
int factor();

#define EXPR_RSLT_FORWARD_REF	1
#define EXPR_RSLT_INT			2

struct EXPRESSIONRESULT {
	int intResult;
	int resultType;
};

extern bool forwardRefFound;

typedef struct EXPRESSIONRESULT EXPRESSIONRESULT;

#endif /* EXPRESSIONS_H_ */
