/*
 * labels.c
 *
 *  Created on: Mar 18, 2015
 *      Author: HICKSK
 */
#include "labels.h"
#include "utils.h"
#include "constants.h"
#include "globals.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

//Sets the position of an already defined label
void setLabelPosition(char* labelName, int position) {
	LABELTABLEENTRY* tail = context.firstLabelEntry;

	while (tail != NULL) {
		if (!strcmp(tail->name, labelName)) {
			tail->position = position;
			tail->definedPosition = TRUE;
			return;
		}

		tail = tail->nextEntry;
	}

	emitLabelsToListing();

	printf("Unknown Label: %s", labelName);
	exit(0);
}

//adds a new label to our table
void addLabelName(char* labelName, int lineNumber) {

	if (labelExists(labelName)) {
		printf("Duplicate Label definition: %s", labelName);
		exit(0);
	}

	LABELTABLEENTRY* tail = context.firstLabelEntry;

	if (tail == NULL) {
		context.firstLabelEntry = malloc(sizeof(LABELTABLEENTRY));
		tail = context.firstLabelEntry;
	} else {
		while (tail->nextEntry != NULL) {
			tail = tail->nextEntry;
		}
		tail->nextEntry = malloc(sizeof(LABELTABLEENTRY));
		tail = tail->nextEntry;
	}

	strcpy(tail->name, labelName);
	tail->position = 0;
	tail->lineNumber = context.currFile->lineNumber;
	tail->definedPosition = FALSE;
	tail->nextEntry = NULL;
}

void emitLabelsToListing() {
	fprintf(context.listingFile->file, "\n\nLABELS:\n");

	LABELTABLEENTRY* head = context.firstLabelEntry;

	while (head != NULL) {
		fprintf(context.listingFile->file, "%06d %-10s %08X\n", head->lineNumber, head->name, head->position);

		head = head->nextEntry;
	}
}

bool labelExists(char* labelName) {
	LABELTABLEENTRY* tail = context.firstLabelEntry;

	while (tail != NULL) {
		if (!strcmp(tail->name, labelName)) {
			return TRUE;
		}

		tail = tail->nextEntry;
	}
	return FALSE;
}

void clearLabelPositionssAfter(char* labelName) {

}

bool labelExistsAndPositionDefined(char* labelName) {
	LABELTABLEENTRY* tail = context.firstLabelEntry;

	while (tail != NULL) {
		if (!strcmp(tail->name, labelName) && tail->definedPosition) {
			return TRUE;
		}

		tail = tail->nextEntry;
	}
	return FALSE;
}

int getPositionOfLabel(char* labelName) {
	LABELTABLEENTRY* tail = context.firstLabelEntry;

		while (tail != NULL) {
			if (!strcmp(tail->name, labelName) && tail->definedPosition) {
				return tail->position;
			}

			tail = tail->nextEntry;
		}
		return 0;
}

/*
 start
 jump mid
 jump start
 mid
 jump end
 end

 start
 jump mid
 jump start
 mid
 jump end
 end


 */
