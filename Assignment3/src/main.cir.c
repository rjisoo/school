/*
	Geoffrey Corey		Oct 27, 2011
	<collaborators, description of help>
	Assignment3 main.cir.c
	Eclipse CDT in Ubuntu 11.10
*/

#include "cirListDeque.h"
#include <stdio.h>
#include <malloc.h>

int main(void)
{
	struct cirListDeque* q = (struct cirListDeque*)malloc(sizeof(struct cirListDeque));
		initCirListDeque(q);
		int i;
		printf("\nAdding to list...\n");
		for (i = 0; i < 20; i++){
			addFrontCirListDeque(q, (TYPE) i+1);
		}
		printCirListDeque(q);

		removeFrontCirListDeque(q);
		printCirListDeque(q);

		reverseCirListDeque(q);
		printCirListDeque(q);

		return 0;
}
