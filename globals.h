/*
 * globals.h
 *
 *  Created on: Mar 12, 2015
 *      Author: HICKSK
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "assemble.h"

extern ASSEMBLECONTEXT context;
extern INSTRUCTION instruction;

extern int inFilePos;
extern int outFilePos;
extern int lstFilePos;
extern int preInsAddr;

#define DEBUG 1

#endif /* GLOBALS_H_ */
