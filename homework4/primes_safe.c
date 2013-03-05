//#define _POSIX_C_SOURCE 199309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <pthread.h>

#define MAX_N 4294967295
#define COMPOSITE 1
#define PRIME 1
#define MAX_THREADS 50 /* sanity number */
#define MAX_PROCESSES 200

void usage(void);
int getInput(int argc, char *argv[], int *method);
unsigned char *sieve_init(long limit);
long sieving(unsigned char *list, long limit);
void markMultiples(unsigned char *list, long index, long limit, long *count);

int main(int argc, char *argv[])
{

	unsigned char *list;
	pthread_t *threads;
	long limit = MAX_N, result;
	int method, number;

	number = getInput(argc, argv, &method);

	if(method == 1){
		fprintf(stdout, "Processes method not yet implemented.\n");
		exit(EXIT_SUCCESS);
	}

	if((threads = (pthread_t*)calloc(number, sizeof(pthread_t))) == NULL){
		fprintf(stderr, "threads: memory allocation failure.\n");
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	if(method == 0) {
		fprintf(stdout, "Method chosen: threads.\nNumber of threads: %d.\n", number);
	}
	if(method == 1) {
		fprintf(stdout, "Method chosen: processes.\nNumber of processes: %d.\n", number);
		fprintf(stdout, "limit is: %ld\n", limit);
	}
#endif

	if((list = sieve_init(limit)) == NULL){
		free (threads);
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	if(list != NULL) {
		fprintf(stdout, "Sieve initialized properly.\n");
	}
#endif

	result = sieving(list, limit);

	fprintf(stdout, "Number of primes found: %ld.\n", result);

	//sleep(5);
	free(list);
	exit(EXIT_SUCCESS);
}

void usage(void)
{
	fprintf(stderr,
			"\nUsage: primes method number\n\n"
					"method: 	use either processes or threads to calculate primes\n"
					"		valid options: thread or process\n"
					"number: 	number of processes/threads to use\n"
					"		valid range: [1-25]\n\n");
	exit(EXIT_FAILURE);
}

int getInput(int argc, char *argv[], int *method)
{
	int number;

	if (argc != 3) {
		fprintf(stderr, "Invalid usage.\n");
		usage();
	}

	if (strcmp("thread", argv[1]) == 0) {
#ifdef DEBUG
		fprintf(stderr, "Using threads.\n");
#endif
		(*method) = 0;
	} else if (strcmp("process", argv[1]) == 0) {
#ifdef DEBUG
		fprintf(stdout, "Using processes.\n");
#endif
		(*method) = 1;
	} else {
		fprintf(stderr, "Invalid flag: %s.\n", argv[1]);
		usage();
	}

	sscanf(argv[2], "%d", &number);
	/*if (number < 1 || number > MAX_THREADS) {

	}*/

	if((*method) == 1){
		if(number > MAX_PROCESSES){
			fprintf(stderr, "Invalid number: %s.\n", argv[2]);
			usage();
		}
	}

	if((*method) == 0){
		if(number > MAX_THREADS){
			fprintf(stderr, "Invalid number: %s.\n", argv[2]);
			usage();
		}
	}

	return number;

}

unsigned char *sieve_init(long limit)
{
	unsigned char *temp;
#ifdef DEBUG
	fprintf(stdout, "Initializing the list.\n");
#endif
	temp = (unsigned char*) calloc((limit + 1) / 8, sizeof(unsigned char));
	if (temp == NULL ) {
		fprintf(stderr, "Memory allocation failure.\n");
	}
	return temp;
}

long sieving(unsigned char *list, long limit)
{

	long i, count;
	int rootlimit;

	rootlimit = sqrt(limit);
	count = limit - 1;

#ifdef DEBUG
	fprintf(stdout, "sqrt of %ld: %d.\n", limit, rootlimit);
	fprintf(stdout, "count starts: 0.\n");
#endif

	//these are really just special values
	list[0 >> 3] |= (COMPOSITE << (0 & (8 - 1))); /* list[0] = COMPOSITE */
	list[1 >> 3] |= (COMPOSITE << (1 & (8 - 1))); /* list[1] = COMPOSITE */

	/* beginning sieve */
	for (i = 3; i <= rootlimit; i++) {
		/*if(list[i] == PRIME)*/
		if (!(list[i >> 3] & (COMPOSITE << (i & (8 - 1))))) {
			/* We found a prime, mark its multiples */
			markMultiples(list, i, limit, &count);
		}
	}
#ifdef DEBUG
	fprintf(stdout, "counted primes: %ld.\n", count);
#endif

	return count;
}

void markMultiples(unsigned char *list, long index, long limit, long *count)
{

	long j;

	for (j = index * index; j <= limit; j += index) {
		/*if(list[j] == 0)*/
		if (!(list[j >> 3] & (COMPOSITE << (j & (8 - 1))))) {
			/* Found a multiple, mark it composite */
			/* list[j] = 1 */
			list[j >> 3] |= (COMPOSITE << (j & (8 - 1)));
			--(*count);
		}
	}
}
