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

typedef struct MACROTABLEENTRY MACROTABLEENTRY;
typedef struct ASSEMBLECONTEXT ASSEMBLECONTEXT;
typedef struct LABELTABLEENTRY LABELTABLEENTRY;
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
};

//Entry in linked list of Macros
struct MACROTABLEENTRY {
	MACROTABLEENTRY* nextEntry;	//Points to the next entry in a linked list
	char* name;					//The defined name of the macro
	char* text;					//What the macro represents
};

//Entry in linked list of Labels
struct LABELTABLEENTRY {
	LABELTABLEENTRY* nextEntry;	//Points to the next entry in a linked list
	int size;					//
	char name[MAX_TOKEN_SIZE];					//The defined name of the label
	int type;					//
	int position;				//The location the label is located
};

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
//Perform Pass2. Assemble instructions, output to output file & listing file
void pass2();

//Print all the labels, and there positions to the listings file
void emitLabelsToListing();
//Add a label to the Label Table
void addLabel(char* labelName, int position);

#endif /* ASSEMBLE_H_ */
