#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>

#define COMPOSITE 1
#define SPECIAL -1
int *allnum;

int init_List(int size);
int print_List(int nums[], int size);
int remove_List(void);
int find_Primes(int nums[], int size);

int main(int argc, char *argv[]){

	int *primes, num_primes, n;

	printf("Please enter the number of primes you want to find:\n");
	scanf("%d", &n);
	printf("You entered: %d\n", n);

	init_List(n);

	return 1;
}

int init_List(int size){

	int i;

	allnum = (int *)calloc(size, sizeof(int));
	assert (allnum != NULL);

	for (i = 0; i < size; i++){
		allnum[i] = i+1;
	}
	return 1;
}

int print_List(int nums[], int size){
	int i;
	for (i = 0; i < size; i++){
		printf("Index: %d, Value: %d\n", i, nums[i]);
	}
	return 1;
}

int remove_List(void){
	free(allnum);
	return 1;
}

int find_Primes(int nums[], int size){
	allnum[0] = SPECIAL;
	int p = 2, i = 2;
	while (p <= sqrt(size)){
		allnum[p*i -1] = COMPOSITE;
	}

	return 1;
}
