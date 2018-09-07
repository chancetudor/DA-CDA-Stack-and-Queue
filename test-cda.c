#include <stdio.h>
#include <stdlib.h>
#include "cda.h"
#include "integer.h"

/*
CDA Test Suite
Version 2
Created by Lusth
Modified by Ben Gerszewski
*/

#define LOOPSIZE 5000

int main(void) {
	int count = 0;
	srand(10);
	CDA *d = newCDA();
	setCDAdisplay(d, displayINTEGER);
	setCDAfree(d, freeINTEGER);
	printf("doing a bunch of inserts\n");
	for (int i = 0; i < LOOPSIZE; ++i) {
		insertCDAfront(d, newINTEGER(rand() % 1000));
		++count;
		insertCDAback(d, newINTEGER(rand() % 1000));
		++count;
	}
	printf("doing a bunch of random inserts\n");
	for (int i = 0; i < LOOPSIZE; ++i) {
		int index = rand() % sizeCDA(d);
		insertCDA(d, index, newINTEGER(rand() % 1000)); //mostly insert middle
		++count;
	}
	printf("size: %d\n", sizeCDA(d));
	printf("randomly doing a bunch of inserts and deletes\n");
	for (int i = 0; i < LOOPSIZE; ++i) {
		int mode = rand() % 6;
		if (mode == 0) { //insert back
			insertCDAback(d, newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 1) { //insert middle
			insertCDA(d, rand() % sizeCDA(d), newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 2) { //insert front
			insertCDAfront(d, newINTEGER(rand() % 1000));
			++count;
		}
		else if (mode == 3 && count > 0) { //remove back
			freeINTEGER(removeCDAback(d));
			--count;
		}
		else if (mode == 4 && count > 0) { //remove middle
			freeINTEGER(removeCDA(d, rand() % sizeCDA(d)));
			--count;
		}
		else if (count > 0) { //remove front
			freeINTEGER(removeCDAfront(d));
			--count;
		}
	}
	printf("new size: %d\n", sizeCDA(d));
	printf("doing a bunch of random removes\n");
	while (count > 10) {
		freeINTEGER(removeCDA(d, rand() % sizeCDA(d))); //remove middle
		--count;
	}
	printf("array d:");
	displayCDA(d, stdout);
	printf("\n");
	freeCDA(d);
	printf("CDA freed\n");
	return 0;
}
