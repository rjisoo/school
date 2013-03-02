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
#define MAX_THREADS 25 /* sanity number */

struct sieve{
	unsigned char *numbers;
	const long limit = MAX_N;
	long count;
};

void usage(void);
int getInput(int argc, char *argv[], int *method);
void init(struct sieve *list);

int main(int argc, char *argv[])
{
	struct sieve list;

	init(&list);

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
	if (number < 1 || number > MAX_THREADS) {
		fprintf(stderr, "Invalid number: %s.\n", argv[2]);
		usage();
	}

	return number;

}

void init(struct sieve *list)
{
	list->numbers = (unsigned char *)calloc((long)((MAX_N + 1)/8), sizeof(unsigned char));
	if (list->numbers == NULL){
		fprintf(stderr, "List: memory allocation failure.\n");
		exit(EXIT_FAILURE);
	}

	list->count = MAX_N - 1;
#ifdef DEBUG
	fprintf(stdout,"Limit = %ld, Count starts: %ld.\n", list->limit, list->count);
#endif
}
