/*
 * assemble.h
 *
 *  Created on: Mar 11, 2015
 *      Author: HICKSK
 */

#ifndef ASSEMBLE_H_
#define ASSEMBLE_H_


#include "stdio.h"
#include "constants.h"
#include "instructions.h"
#include "utils.h"
#include "labels.h"

typedef struct MACROTABLEENTRY MACROTABLEENTRY;
typedef struct ASSEMBLECONTEXT ASSEMBLECONTEXT;
typedef struct FILECONTEXT FILECONTEXT;

//The information about the entire assembling process
struct ASSEMBLECONTEXT {
	int fileDepth;				//How deep in recursion are we assembling files

	FILECONTEXT* currFile; 		//The file we are currently assembling. This points to the tail of a liked list of files

	FILECONTEXT* unifiedFile;	//The result of pass0
	FILECONTEXT* interFile;		//The result of pass1
	FILECONTEXT* outputFile;	//The result of pass2
	FILECONTEXT* listingFile;	//Human readable output of pass2

	MACROTABLEENTRY* firstMacroEntry;	//Points to the head of a linked list of macros
	LABELTABLEENTRY* firstLabelEntry;	//Points to the head of a linked list of labels

	int outputPos;				//The position in the output binary
	bool foundForwardReference;	//A boolean, set if we have found a forward reference. This signals the need for a new virtual block in pass 1
};

//Entry in linked list of Macros
struct MACROTABLEENTRY {
	MACROTABLEENTRY* nextEntry;	//Points to the next entry in a linked list
	char* name;					//The defined name of the macro
	char* text;					//What the macro represents
};


#define CTX_BITS_16			16
#define CTX_BITS_32			32
#define CTX_BITS_DEFAULT	CTX_BITS_32

//Entry in linked list of files
struct FILECONTEXT {
	FILE* file;							//The system reference to the file
	FILECONTEXT* parentFile;			//Points to the previous file we were assembling before we started this one
	int lineNumber;						//The lineNumber we are currently assembling
	int charNumber;						//The column of the lookAhead char
	char lookAhead;						//A single char giving us a preveiw of whats ahead of the the current token in the lineBuffer.
	int lookAheadPosition;				//The position in the lineBuffer that the lookAhead is at
	char tokenBuffer[MAX_TOKEN_SIZE];	//The current token/identifier/number
	int numberTokenValue;				//If the current token is a number, then this will hold its actual value
	char lineBufferLookAhead;			//The look ahead character looking at the next character from the file
	char lineBuffer[MAX_LINE_BUFFER_SIZE];	//The text of the line we are currently assembling

	int bitMode;							//16, or 32 bit

	INSTRUCTION* insDesc;
	int inseideQuotes;
};

//Prepare for assembly
void beginAssembly();
//Finsih assembly. Close files, and cleanup
void endAssembly();

//Assemble the file
void assembleFile(char* fileName);
//Perform Pass0. Looking for Preprocessor directives
void pass0();
//Perform Pass1. Counting instruction sizes, and collecting labels
void pass1();
//During pass 1, we may break up the code into chuncks to better find the most effecient forms of reletive displacements
void pass1_block();
//Perform Pass2. Assemble instructions, output to output file & listing file
void pass2();

#endif /* ASSEMBLE_H_ */
