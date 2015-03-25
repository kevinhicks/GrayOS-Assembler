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

	FILECONTEXT* unifiedFile;	//The result of pass1
	FILECONTEXT* outputFile;	//The result of pass2
	FILECONTEXT* listingFile;	//Human readable output of pass2

	MACROTABLEENTRY* firstMacroEntry;	//Points to the head of a linked list of macros
	LABELTABLEENTRY* firstLabelEntry;	//Points to the head of a linked list of labels

	int outputPos;				//The position in the output binary
	bool foundForwardReference;	//A boolean, set if we have found a forward reference. This signals the need for a new virtual block in pass 1

	int bitMode;
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
	char lineBufferLookAhead;			//The look ahead character looking at the next character from the file
	char lineBuffer[MAX_LINE_BUFFER_SIZE];	//The text of the line we are currently assembling

	int insideQuotes;
};

//Prepare for assembly
void beginAssembly();
//Finsih assembly. Close files, and cleanup
void endAssembly();

//Assemble the file
void assembleFile(char* fileName);

#endif /* ASSEMBLE_H_ */
