#define _POSIX_C_SOURCE 199309

#include <iostream>
using std::cin;
using std::cout;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <vector>

#define MAX_STR_LEN 200

void wait_for(int processes);
void suppressor(int processes, int **fds);
void close_file(int processes, FILE **streams);
int get_arguments(int argc, char *argv[]);
void create_pipe(int processes, int **toSort, int **fromSort);
void sorter(int processes, int **toSort, int **fromSort);
void parser(int processes, int **toSort, int **fromSort);
void read_pipe(int position, std::vector<std::string> &cache, FILE **BACK, int *timeout);
int get_word(char *word);
static char *to_lower(char *str);
void signalHandler(int signum, siginfo_t *info, void *ptr);

pid_t *pids; /* needed to be a global variable for signal handling */
int processes;

int main(int argc, char *argv[])
{

	exit(EXIT_SUCCESS);
}

void wait_for(int process)
{
	int status;
	for (int i = 0; i < process; i++) {
		wait(&status);
	}
}

void suppressor(int processes, int **fds)
{

}

void close_file(int processes, FILE **streams)
{

	int i;
	for (i = 0; i < processes; i++) {
		fclose(streams[i]);
	}
	free(streams);
}

int get_arguments(int argc, char *argv[])
{

	int process_number;

	if (argc > 2 || argc < 2) {
		fprintf(stderr, "Usage: uniqify -[number > 0]\n");
		exit(EXIT_FAILURE);
	} else {
		sscanf(argv[1] + 1, "%d", &process_number);
	}
	return process_number;
}

void create_pipe(int processes, int **toSort, int **fromSort)
{

	int i;
	for (i = 0; i < processes; i++) {
		if (pipe(toSort[i]) == -1) {
			perror("toSort pipe");
			exit(EXIT_FAILURE);
		}
		if (pipe(fromSort[i]) == -1) {
			perror("fromSort pipe");
			exit(EXIT_FAILURE);
		}
	}
}

void sorter(int processes, int **toSort, int **fromSort)
{

}

void parser(int processes, int **toSort, int **fromSort)
{

	FILE **output;
	char word[200];
	int i;

	output = (FILE**) calloc(processes, sizeof(FILE*));

	if (output == NULL ) {
		perror("file stream allocation");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < processes; i++) {
		close(toSort[i][0]);
		close(fromSort[i][0]);
		close(fromSort[i][1]);
		output[i] = fdopen(toSort[i][1], "w");
	}
	i = 0;
	while (get_word(word) > 0) {
		fputs(word, output[i]);
		if (i == processes - 1) {
			i = 0;
		} else {
			i++;
		}
	}
	close_file(processes, output);
}

int get_word(char *word)
{

	int length = 0;
	if (fscanf(stdin, "%198[A-Za-z']%*[^A-Za-z']", word) > 0) {
		strcat(word, "\n");
		to_lower(word);
		length = strlen(word);
	}
	return length;
}

void read_pipe(int position, std::vector<std::string> &cache, FILE **BACK, int *timeout) {

}

/* http://stackoverflow.com/questions/6857445/lowercase-urls-in-varnish-inline-c */
static char *to_lower(char *str)
{
	char *s = str;
	while (*s) {
		if (isupper(*s)) {
			*s = tolower(*s);
		}
		s++;
	}
	return str;
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{
	int status, i;
	//printf("\nSignal: %d\n", signum);
	//kill(pids[0], signum);
	//wait(&status);
	for (i = 0; i < processes; i++) {
		kill(pids[i], SIGKILL);
		wait(&status);
	}
	exit(EXIT_FAILURE);
}
