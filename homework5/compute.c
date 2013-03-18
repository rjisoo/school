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

int main(int argc, char *argv[]) {

	long iops, min, max;
	int i;
	char sendline[MAXLINE], recvline[MAXLINE];
	pthread_mutex_t thread_lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_t id;

	/* Connect to server */
	sockfd = initClient(argv[1], atoi(argv[2]));

	/* Benchmark system */
	fprintf(stdout, "Benchmarking system...\n");
	iops = getIOPS();

	/*format data */
	sprintf(sendline, "i%ld", iops);
	fprintf(stdout, "IOPS: %s\n", sendline);

	/* send IOPS */
	send(sockfd, sendline, strlen(sendline) - 1, 0);

	if (recv(sockfd, recvline, MAXLINE, 0) == 0) {
		//error: server terminated prematurely
		fprintf(stderr, "The server terminated prematurely.\n");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	sscanf(recvline, "%ld, %ld", &min, &max);

	fprintf(stdout, "Range received: %ld, %ld\n", min, max);

	struct threadargs ta = {min, max, &thread_lock};

	while (1) {

		pthread_create(&id, NULL, worker, (void*)&ta);
		pthread_join(id, NULL);

		for(i = 0; i < numfound; i++){
			if(flag){
				sprintf(sendline, "p%ld", perfect[new_num++]);
				send(sockfd, sendline, strlen(sendline), 0);
				if (recv(sockfd, recvline, MAXLINE, 0) == 0) {
							//error: server terminated prematurely
							fprintf(stderr, "The server terminated prematurely.\n");
							close(sockfd);
							exit(EXIT_FAILURE);
						}
			}
		}
		fprintf(stdout, "\n");

		sprintf(sendline, "%ld", max);

		send(sockfd, sendline, strlen(sendline), 0);
		if (recv(sockfd, recvline, MAXLINE, 0) == 0) {
			//error: server terminated prematurely
			fprintf(stderr, "The server terminated prematurely.\n");
			close(sockfd);
			exit(EXIT_FAILURE);
		}

		sscanf(recvline, "%ld, %ld", &min, &max);

		fprintf(stdout, "Range received: %ld, %ld\n", min, max);
		ta.min = min;
		ta.max = max;
		sleep(1);
	}
	close(sockfd);
	sleep(1);
	exit(EXIT_SUCCESS);
}

void signalHandler(int signum, siginfo_t *info, void *ptr) {

	close(sockfd);
	exit(EXIT_SUCCESS);
}

int initClient(char *ipaddr, int port) {
	struct sockaddr_in servaddr;
	int mysocket;

	if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Problem in creating the socket");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ipaddr);
	servaddr.sin_port = htons(port);

	if (connect(mysocket, (struct sockaddr *) &servaddr, sizeof(servaddr))
			< 0) {
		perror("Problem in connecting to the server");
		close(mysocket);
		exit(EXIT_FAILURE);
	}

	return mysocket;
}

long getIOPS(void) {

	long i, j, k, lim;
	double result;

	lim = 100000000;

	clock_t begin, end;

	j = 10;

	begin = clock();
	for (i = 0; i < lim; i++) {
		k = i % j;
	}
	end = clock();

	result = (double) (end - begin) / CLOCKS_PER_SEC;
	k = (long) lim / result;

	return k;
}

long testPerfectNumber(long value) {

	long i = 1, sum = 0;

	while (i < value) {
		if (value % i == 0) {
			sum = sum + i;
		}
		i++;
	}
	if (sum == value) {
		return value;
	} else {
		return 0;
	}
}

void *worker(void* ptr)
{
	struct threadargs *ta = (struct threadargs *)ptr;

	long i, result;
	int found = 0;
	new_num = numfound;


	for(i = ta->min; i < ta->max; i++){
		if((result = testPerfectNumber(i)) > 0){
			perfect[numfound++] = result;
			found++;
		}
	}

	if(found){
		flag++;
	} else {
		flag = 0;
	}

	pthread_exit(NULL);

}
