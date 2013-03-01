//#define _POSIX_C_SOURCE 199309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>


#define MAX 4294967295
#define COMPOSITE 1
#define PRIME 1

int get_input(int argc, char *argv[], int *method);
uint8_t *sieve_init(long limit);
long sieving(uint8_t *list, long limit);
void mark_composite(uint8_t *list, long index, long limit, long *count);

int main(int argc, char *argv[])
{

	uint8_t *list;
	long limit;
	long result;
	int method;
	int number;

	number = get_input(argc, argv, &method);

	limit = MAX;

#ifdef DEBUG
	fprintf(stdout, "limit is: %ld\n", limit);
#endif

	list = sieve_init(limit);

#ifdef DEBUG
	if(list != NULL){
		fprintf(stdout, "Sieve initialized properly.\n");
	}
#endif

	result = sieving(list, limit);

	fprintf(stdout, "Number of primes found: %ld.\n", result);

	//sleep(5);
	free(list);
	exit(EXIT_SUCCESS);
}

int get_input(int argc, char *argv[], int *method){

	int number;
	int flag;

	if(argc < 3 || argc > 3){
		//print error
		exit(EXIT_FAILURE);
	}
	return 0;
}

uint8_t *sieve_init(long limit)
{
	uint8_t *temp;
#ifdef DEBUG
	fprintf(stdout, "Initializing the list.\n");
#endif
	temp = (uint8_t*)calloc((limit+1)/8, sizeof(uint8_t));
	if(temp == NULL){
		fprintf(stderr, "Memory allocation failure.\n");
		exit(EXIT_FAILURE);
	} else {
		return temp;
	}

}

long sieving(uint8_t *list, long limit)
{

	long i, count;
	int rootlimit;

	rootlimit = sqrt(limit);
	count = limit -1;

#ifdef DEBUG
	fprintf(stdout, "sqrt of %ld: %d.\n", limit, rootlimit);
	fprintf(stdout, "count starts: %ld.\n", count);
#endif
	list[0] = list[1] = COMPOSITE; //these are really just special values

	/* beginning sieve */
	for(i = 2; i <= rootlimit; i++){
		/*if(list[i] == PRIME)*/
		if(!(list[i>>3]&(COMPOSITE<<(i&(8-1))))){
			mark_composite(list, i, limit, &count);
			/* we found a prime, mark its multiples */
			//for(j = i*i; j <= limit; j += i){
				/*if(list[j] == 0)*/
				//if(!(list[j>>3]&(COMPOSITE<<(j&(8-1))))){
					/* Found a multiple, mark it composite */
					/* list[j] = 1 */
				//	list[j>>3] |= (COMPOSITE<<(j&(8-1)));
				//	count--;
				//}
			//}
		}
	}
#ifdef DEBUG
	fprintf(stdout, "counted primes: %ld.\n", count);
#endif


	return count;
}

void mark_composite(uint8_t *list, long index, long limit, long *count)
{

	long j;

	for(j = index*index; j <= limit; j += index){
		/*if(list[j] == 0)*/
		if(!(list[j>>3]&(COMPOSITE<<(j&(8-1))))){
			/* Found a multiple, mark it composite */
			/* list[j] = 1 */
			list[j>>3] |= (COMPOSITE<<(j&(8-1)));
			--(*count);
		}
	}
}
