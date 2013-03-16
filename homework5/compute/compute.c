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
	sockfd = initClient(argv[1], atoi(argv[2]));

	close(sockfd);
	exit(EXIT_SUCCESS);
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{


}

int initClient(char *ipaddr, int port)
{
	struct sockaddr_in servaddr;
	int mysocket;

	if((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Problem in creating the socket");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr= inet_addr(ipaddr);
	servaddr.sin_port =  htons(port);

	if(connect(mysocket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		perror("Problem in connecting to the server");
		close(mysocket);
		exit(EXIT_FAILURE);
	}

	return mysocket;
}
