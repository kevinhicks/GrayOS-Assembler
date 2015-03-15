/*
 * directives.h
 *
 *  Created on: Mar 7, 2015
 *      Author: keyho_000
 */

#ifndef DIRECTIVES_H_
#define DIRECTIVES_H_

#include "utils.h"

#define DRTV_NOT_FOUND	-1
#define DRTV_INCLUDE	0
#define DRTV_DEFINE		1
#define DRTV_IFDEF		2
#define DRTV_ENDIF		3
#define DRTV_BASE		4
#define DRTV_BITS		5
#define DRTV_DB			6
#define DRTV_DW			7
#define DRTV_DD			8
#define DRTV_DQ			9

#define DRTV_PHASE0		1
#define DRTV_PHASE1		2
#define DRTV_PHASE2		4
#define DRTV_ANY		DRTV_PHASE0 | DRTV_PHASE1 | DRTV_PHASE2

int findDirective(char* ident, int phase);

void doDirective(int directive);
void findAndDoDirective(FILECONTEXT* context);

void doDeclareBytes();

void doInclude();
#endif /* DIRECTIVES_H_ */
