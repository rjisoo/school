#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define MAX_N 4294967295
//#define MAX_N 1000000000
#define COMPOSITE 1
#define PRIME 1
#define MAX_THREADS 50 /* sanity number */
#define MAX_PROCESSES 200

struct threadargs {
   long n;  // max number to check for primeness
   int *nbptr;  // nextbase
   unsigned char *primearray;  // array recording prime/composite
   pthread_mutex_t *lockptr;  // lock pointer
};

void crossout(long k, long limit, unsigned char *primearr);
void *worker(void* ptr);
void usage(void);
int getInput(int argc, char *argv[], int *method);
void printPrimes(unsigned char* primearr);

int main(int argc, char *argv[])
{

	long numprimes, i, work;
	int method, number;

	number = getInput(argc, argv, &method);

	unsigned char *prime = (unsigned char*)calloc((long)(MAX_N + 1)/8, sizeof(unsigned char));
	prime[0 >> 3] |= (COMPOSITE << (0 & (8 - 1))); /* list[0] = COMPOSITE */
	prime[1 >> 3] |= (COMPOSITE << (1 & (8 - 1))); /* list[1] = COMPOSITE */

	int nextbase = 3;

	pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;

	pthread_t id[number];
	struct threadargs thrdargs[number];

#ifdef DEBUG
	if(method == 0) {
		fprintf(stdout, "Method chosen: threads.\nNumber of threads: %d.\n", number);
	}
	if(method == 1) {
		fprintf(stdout, "Method chosen: processes.\nNumber of processes: %d.\n", number);
	}
#endif
	if(method == 1){
		fprintf(stdout, "Feature not yet implemented.\n");
		free(prime);
		exit(EXIT_SUCCESS);
	}


#ifdef DEBUG
	fprintf(stdout, "Beginning threading.\n");
#endif

	for(i = 0; i < number; i++){
		thrdargs[i].n = MAX_N;
		thrdargs[i].nbptr = &nextbase;
		thrdargs[i].primearray = prime;
		thrdargs[i].lockptr = &nextbaselock;
		pthread_create(&id[i], NULL, worker, (void*)&thrdargs[i]);
	}

#ifdef DEBUG
	fprintf(stdout, "Waiting for threads to finish.\n");
#endif

	for(i = 0; i < number; i++){
		pthread_join(id[i], (void*)&work);
#ifdef DEBUG
	fprintf(stdout, "Work done by thread %ld: %ld.\n", i+1, work);
#endif
	}

	numprimes = 1;

#ifdef DEBUG
	fprintf(stdout, "Counting primes.\n");
#endif

	for (i = 3; i < MAX_N; i++) {
		if (i % 2 != 0) {
			if (!(prime[i >> 3] & (COMPOSITE << (i & (8 - 1))))) {
				numprimes++;
			}
		}
	}

	if (argc == 4) {
		if (strcmp(argv[3], "print") == 0) {
			printPrimes(prime);
		}
	} else {
		fprintf(stdout, "Number of primes: %ld\n.", (numprimes));
	}

	free(prime);
	exit(EXIT_SUCCESS);
}

void crossout(long k, long limit, unsigned char *primearr)
{
	long i;

	for(i = 3; i*k <= limit; i+=2){
		primearr[(i*k) >> 3] |= (COMPOSITE << ((i*k) & (8 - 1)));
	}

}

void *worker(void* ptr)
{
	struct threadargs *ta;
	long rootlimit;
	long base;
	long limit;
	long work;
	unsigned char *primes;
	pthread_mutex_t *lock;

	ta = (struct threadargs*) ptr;
	limit = ta->n;
	work = 0;
	primes = ta->primearray;
	lock = ta->lockptr;
	rootlimit = sqrt(limit);

	do {
		pthread_mutex_lock(lock);
		base = *(ta->nbptr);
		*(ta->nbptr) += 2;
		pthread_mutex_unlock(lock);

		if (base <= rootlimit) {
			if (!(primes[base >> 3] & (COMPOSITE << (base & (8 - 1))))) {
				pthread_mutex_lock(lock);
				crossout(base, limit, primes);
				pthread_mutex_unlock(lock);
				work++;
			}
		} else {
			break;
		}

	} while (1);



	pthread_exit((void*) work);

}

void usage(void)
{
	fprintf(stderr,
			"\nUsage: primes method number {print}\n\n"
					"method: 	use either processes or threads to calculate primes\n"
					"		valid options: thread or process\n"
					"number: 	number of processes/threads to use\n"
					"		valid range processes: [1-%d] threads: [1-%d]\n\n", (int)MAX_PROCESSES, (int)MAX_PROCESSES);
	exit(EXIT_FAILURE);
}

int getInput(int argc, char *argv[], int *method)
{
	int number;

	if (argc < 3 || argc > 4) {
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

	if((*method) == 1){
		fprintf(stdout, "Processes method not yet implemented.\n");
		exit(EXIT_SUCCESS);
	}

	sscanf(argv[2], "%d", &number);
	/*if (number < 1 || number > MAX_THREADS) {

	 }*/

	if ((*method) == 1) {
		if (number > MAX_PROCESSES) {
			fprintf(stderr, "Invalid number: %s.\n", argv[2]);
			usage();
		}
	}

	if ((*method) == 0) {
		if (number > MAX_THREADS) {
			fprintf(stderr, "Invalid number: %s.\n", argv[2]);
			usage();
		}
	}

	return number;

}

void printPrimes(unsigned char* primearr)
{
	long i;

	for(i = 3; i < MAX_N; i+=2){
		if (!(primearr[i >> 3] & (COMPOSITE << (i & (8 - 1))))){
			fprintf(stdout, "%ld is prime.\n", i);
		} else {
			fprintf(stdout, "%ld is not prime.\n", i);
		}
	}

}
