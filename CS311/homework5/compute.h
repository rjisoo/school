#ifndef _COMPUTE_H
#define _COMPUTE_H

/* Function prototypes */
void signalHandler(int signum, siginfo_t *info, void *ptr);
int initClient(char *ipaddr, int port);
void *worker(void* ptr);
long getIOPS(void);
long testPerfectNumber(long value);

/* Defines */
#define MAXLINE 4096

/* Global variables (even though they are bad, sometimes needed) */
int numfound = 0;
int sockfd;
int flag;
int new_num = 0;
long perfect[8] = {0};
struct sigaction act;
struct threadargs{
	long min;
	long max;
	pthread_mutex_t *lockptr;
};

#endif
