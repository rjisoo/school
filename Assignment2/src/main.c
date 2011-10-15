/*
 *	Geoffrey Corey		Oct 8, 2011
 *	<collaborators, description of help>
 *	main.c Assignment2
 *	Eclipse CDt in Linux Ubuntu
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "dynArray.h"

int main(){

	struct DynArr* s;
	s = newDynArr(2);
	printf("\nInitial array size; %d\n", sizeDynArr(s));


	printf("\nAdding values to array\n");

	addDynArr(s, 5);
	printf("\nSize of array: %d", sizeDynArr(s));
	printf("\nIsEmpty: %d", isEmptyDynArr(s));
	addDynArr(s, 6);
	printf("\nSize of array: %d", sizeDynArr(s));
	addDynArr(s, 8);
	printf("\nSize of array: %d", sizeDynArr(s));
	addDynArr(s, 9);
	printf("\nSize of array: %d\n", sizeDynArr(s));

	printf("\nValue: %d", getDynArr(s, 0));
	printf("\nValue: %d", getDynArr(s, 1));
	printf("\nValue: %d\n", getDynArr(s, 2));

	putDynArr(s, 0, 1);
	putDynArr(s, 1, 2);
	putDynArr(s, 2, 3);
	putDynArr(s, 3, 4);

	printf("\nValue: %d", getDynArr(s, 0));
	printf("\nValue: %d", getDynArr(s, 1));
	printf("\nValue: %d", getDynArr(s, 2));
	printf("\nValue: %d\n", getDynArr(s, 3));

	printf("\nSwapping elements...\n");
	swapDynArr(s, 0, 3);
	swapDynArr(s, 1, 2);

	printf("\nValue: %d", getDynArr(s, 0));
	printf("\nValue: %d", getDynArr(s, 1));
	printf("\nValue: %d", getDynArr(s, 2));
	printf("\nValue: %d\n", getDynArr(s, 3));

	printf("\nRemoving values\n");
	removeDynArr(s, 5);
	printf("\nValue: %d", getDynArr(s, 0));
	printf("\nValue: %d", getDynArr(s, 1));
	printf("\nValue: %d", getDynArr(s, 2));
	printf("\nSize of array: %d", sizeDynArr(s));
	printf("\nValue: %d\n", getDynArr(s, 0));





	return 1;
}
