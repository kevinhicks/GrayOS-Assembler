/*
 * labels.h
 *
 *  Created on: Mar 18, 2015
 *      Author: HICKSK
 */

#ifndef LABELS_H_
#define LABELS_H_

#include "constants.h"
#include "utils.h"

typedef struct LABELTABLEENTRY LABELTABLEENTRY;

//Entry in linked list of Labels
struct LABELTABLEENTRY {
	LABELTABLEENTRY* nextEntry;	//Points to the next entry in a linked list
	int size;					//
	char name[MAX_TOKEN_SIZE];	//The defined name of the label
	int type;					//
	int position;				//The location the label is located
	bool definedPosition;		//Do we know the memory location of this label?
	int lineNumber;				//The line number that it is defined
};

//Add a label to the Label Table
void addLabelName(char* labelName, int lineNumber);
//Sets the position of an already defined name
void setLabelPosition(char* labelName, int position);
//Sets the position of all the labels AFTER the specified name to undefined
void clearLabelPositionssAfter(char* labelName);
//Does a label by the specified name exist?
bool labelExists(char* labelName);
//Does the label exist? and is its position defined?
bool labelExistsAndPositionDefined(char* labelName);
//gets the position of a label
int getPositionOfLabel(char* labelName);

//Print all the labels, and there positions to the listings file
void emitLabelsToListing();

#endif /* LABELS_H_ */
