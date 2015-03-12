/*
 * main.c
 *
 *  Created on: Mar 5, 2015
 *      Author: keyho_000
 */

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stddef.h"

#include "parser.h"
#include "constants.h"
#include "opcodes.h"
#include "directives.h"
#include "instructions.h"
#include "assemble.h"

int main() {
	char* inputFileName = "testFiles\\test.src";

	ASSEMBLECONTEXT context;

	FILECONTEXT unifiedFile;
	FILECONTEXT interFile;
	FILECONTEXT outputFile;
	FILECONTEXT listingFile;

	context.unifiedFile = &unifiedFile;
	context.interFile = &interFile;
	context.outputFile = &outputFile;
	context.listingFile = &listingFile;

	beginAssembly(&context);
	assembleFile(&context, inputFileName);
	endAssembly(&context);

	return 0;
}
/*
 void assemble(char* fileName) {

 printf("Assembling: %s\n", fileName);

 ASSEMBLECONTEXT assembleContext;

 FILECONTEXT fileContext;

 fileContext.file = fopen(fileName, "r");
 fileContext.lineNumber = 1;
 fileContext.charNumber = 1;

 //prime the pump
 readChar(&fileContext);
 skipWhitespaceLines(&fileContext);

 assembleFile(&fileContext);

 pass0(&fileContext); 	//Read & Store Macros
 pass1(&fileContext);	//Expand Macros & Count Instructions
 pass2(&fileContext);	//Assemble & Output
 }

 isting file

 void pass0(FILECONTEXT* fileContext) {

 while (fileContext.lookAhead != EOF) {

 readLine(&fileContext);

 assembleLine(&fileContext);

 if (fileContext.lookAhead == ';') {
 //Comment
 skipLine(&fileContext);
 } else if (fileContext.lookAhead == ',') {
 //TODO Handle multiple parameters
 readChar(&fileContext);
 skipWhitespace(&fileContext);
 } else if (fileContext.lookAhead == '#') {
 //Directive
 doDirective(&fileContext);
 } else {
 //Instruction
 doInstruction(&fileContext);
 }

 skipWhitespaceLines(&fileContext);
 }
 fclose(fileContext.file);

 printf("Assemble Complete\n");
 }
 */
