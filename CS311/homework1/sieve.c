#include "sieve.h"
#include <malloc.h>
#include <stdlib.h>
/*#include <math.h>*/
#include <stdio.h>
#include <assert.h>

#define PRIME 0
#define COMPOSITE 1
#define SPECIAL -1

int *numlist, prime_count;

int initList(int size) {

	//initializes array candidate primes
	numlist = (int *) calloc((size + 1), sizeof(int));
	assert(numlist != NULL);
	free(numlist);
	return 1;
}

/* I could not get the sieve algorithm working.
 * It keeps pegging the CPU at 100% and gets stuck at index 2 of the array.
 */
/*int findPrimes(int size) {
	int i,k, m, root;
	k = 1;
	root = sqrt(size);

	numlist[0] = SPECIAL;
	numlist[1] = SPECIAL;
	while (k <= root){
		i = k + 1;
		if (numlist[i] == PRIME){
			m = i;
			for (i = 2; m*i < size; i++){
				numlist[i*m] = COMPOSITE;
				printf("i = %d", i);
			}
		} else {
			i++;
		}
		k = m;
	}

	free(numlist);
	return 1;
}*/
