#ifndef _COMPUTE_H
#define _COMPUTE_H

/* Function prototypes */
void signalHandler(int signum, siginfo_t *info, void *ptr);
int initClient(char *ipaddr, int port);
void *worker(void *ptr);
long getIOPS(void);

/* Defines */
#define LIM 100000000
#define MAXLINE 4096

/* Global variables (even though they are bad, sometimes needed) */
int numfound;
int sockfd;
int flag;
int perfect[8] = {0};
struct sigaction act;
struct threadargs{
	long min;
	long max;
	pthread_mutex_t *lockptr;
};

#endif
