#define _POSIX_C_SOURCE 199309

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "compute.h"

int main(int argc, char *argv[])
{

	long iops;
	long value;
	char input[MAXLINE];
	char output[MAXLINE];
	struct threadargs ta;
	struct sockaddr_in servaddr;
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_t id;

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = signalHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL );
	sigaction(SIGQUIT, &act, NULL );
	sigaction(SIGHUP, &act, NULL );

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));

	ta.lockptr = &lock;
	ta.max = 100000;
	ta.min = 1;

	flag = 0;

#ifdef DEBUG
	fprintf(stderr, "Opening socket.\n");
#endif
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Problem in creating the socket");
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	fprintf(stderr, "connecting.\n");
#endif
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("Problem in connecting to the server");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	iops = getIOPS();
	fprintf(stdout, "IOPS of this machine: %ld IOPS.\n", iops);

	while(1){
			fscanf(stdin, "%s", input);
			send(sockfd, input, strlen(input)+1, 0);
			if (recv(sockfd, output, MAXLINE, 0) == 0) {
				//error: server terminated prematurely
				fprintf(stderr, "The server terminated prematurely.\n");
				close(sockfd);
				exit(EXIT_FAILURE);
			}
			fprintf(stdout, "String received from the server: %s\n", output);
		}

		close(sockfd);

	close(sockfd);
	exit(EXIT_SUCCESS);
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{
#ifdef DEBUG
	fprintf(stderr, "Received signal %d, exiting.\n", signum);
#endif
	close(sockfd);
	exit(EXIT_FAILURE);
}

void *worker(void* ptr)
{

	struct threadargs *ta = (struct threadargs *)ptr;

	sleep(15);


	pthread_exit(NULL);
}

long getIOPS(void)
{

	long i, j, k;
	double result;

	clock_t begin, end;

	j = 10;

	begin = clock();
	for (i = 0; i < LIM; i++) {
		k = i % j;
	}
	end = clock();

	result = (double) (end - begin) / CLOCKS_PER_SEC;
	i = LIM / result;

	j = k++;

#ifdef DEBUG
	fprintf(stdout, "The time elapsed to do %ld mod operations is: %3.2lfs.\n", (long) LIM, result);
	fprintf(stdout, "The total IOPS for this system: %ld IOPS.\n", i);
#endif
	return i;
}
