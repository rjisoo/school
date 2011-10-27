/*
	Geoffrey Corey		Oct 27, 2011
	<collaborators, description of help>
	Assignment3 main.c
	Eclipse CDT in Ubuntu 11.10
*/

#include <stdlib.h>
#include <stdio.h>
#include "dynArray.h"
#include <time.h>

double getMilliseconds() {
   return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(void)
{
	double t1, t2;
	int i = 0;
	int n = 1000;
	/* while (LT(n, 256001)){
	struct bag *b = (struct bag *)malloc(sizeof(struct bag));
	initBag(b);

	printf("\nAdding %d items to bag...\n", n);
	while (LT(i, n)){
		addToBag(b, (TYPE)i);
		i++;
	}

	i = 0;

	printf("Checking contents...\n");
	t1 = getMilliseconds();
	while (LT(i, n)){
			bagContains(b, i);
			i++;
		}
	t2 = getMilliseconds();

	printf("%d %g\n", n, t2-t1);

	n = n*2;

	printf("Resetting bag...\n");
	free(b);
	} */

	printf("\nDone\n");


	return 1;
}
