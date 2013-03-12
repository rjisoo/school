#define _POSIX_C_SOURCE 199309

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>

/* Function prototypes */
void signalHandler(int signum, siginfo_t *info, void *ptr);
void *worker(void *ptr);

/* Defines */

/* Global variables (even though they are bad, sometimes needed) */
struct sigaction act;

int main(int argc, char *argv[])
{

#ifdef DEBUG
	fprintf(stderr, "Initializing routine variables.\n");
#endif

	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_t work;

	struct threadargs ta = {0, 10000, &lock};

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = signalHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL );
	sigaction(SIGQUIT, &act, NULL );
	sigaction(SIGHUP, &act, NULL );

	pthread_create(&work, NULL, worker, (void *)&ta);
	pthread_join(work, NULL);

	exit(EXIT_SUCCESS);
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{
#ifdef DEBUG
	fprintf(stderr, "Received signal %d, exiting.\n", signum);
#endif
	exit(EXIT_FAILURE);
}

void *worker(void *ptr)
{
	struct threadargs *ta;
	int n;
	int i;
	int sum;
	int min;
	int max;
	pthread_mutex_t *lock;

	ta = (struct threadargs *) ptr;

	min = ta->

	pthread_exit(NULL);
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{
	exit(EXIT_FAILURE);
}
