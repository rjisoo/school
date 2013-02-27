//#define _POSIX_C_SOURCE 199309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>

long sieve(uint8_t *sieve, long limit);
uint8_t *initialize(long limit);

#define MAX 4294967296
#define COMPOSITE 1


int main(int argc, char *argv[])
{

	uint8_t *list;
	long limit = MAX;
	long result;

	list = initialize(limit);

	result = sieve(list, limit);

	printf("result: %ld\n", result);

	//sleep(5);

	free(list);
	exit(EXIT_SUCCESS);
}

long sieve(uint8_t *sieve, long limit)
{
	long i, j, count;
	int rootlimit;

	rootlimit = sqrt(limit);
	count = limit -1;

	//sieve[0] = sieve[1] = 0; // mark special, but we don't really care about these.
	//sieve[0>>3] |= (!COMPOSITE<<(0&(8-1)));
	//sieve[1>>3] |= (!COMPOSITE<<(1&(8-1)));

	for(i = 2; i <= rootlimit; i++){

		if(!(sieve[i>>3] & (COMPOSITE<<(i&(8-1))))){ //if sieve[i] == 0
			count++;
			for(j = i*i; j <= MAX; j += i){
				if(!(sieve[j>>3] & (COMPOSITE<<(j&(8-1))))){ //if sieve[j] == 0
					sieve[j>>3] |= (COMPOSITE<<(j&(8-1))); //sieve[i] = 1
					count--;
				}
			}
		}
	}

	return count;
}

uint8_t *initialize(long limit)
{
	uint8_t *sieve;
	sieve = (uint8_t*)calloc((limit+1)/8, sizeof(uint8_t));
	if(sieve == NULL){
		fprintf(stderr, "Memory application failure.\n");
		exit(EXIT_FAILURE);
	} else {
		return sieve;
	}

}
