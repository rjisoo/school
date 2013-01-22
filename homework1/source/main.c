#include "sieve.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int size = 70;
	if (initList(size)){
		findPrimes(size);
	} else {
		printf("Error\n");
	}

	//while (i < size){
	//printf("Index: 	%d, Vlaue: 	%d\n", i, numlist[i]);
	//}

	return 1;
}
