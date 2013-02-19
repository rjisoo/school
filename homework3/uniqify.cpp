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
#define EXIT_STR "zzzzzzz"

void reap(int processes);
void suppressor(int processes, int fds[][2]);
void suppress(int processes, int to_sort[][2], int fr_sort[][2]);
void close_file(int processes, FILE **streams);
int get_arguments(int argc, char *argv[]);
void create_pipe(int processes, int toSort[][2], int fromSort[][2]);
void sorter(int processes, pid_t *pids, int toSort[][2], int fromSort[][2]);
void parser(int processes, int toSort[][2], int fromSort[][2]);
void read_pipe(int position, std::vector<std::string> &temp, FILE **input, int *timeout);
int get_word(char *word);
static char *to_lower(char *str);
void signalHandler(int signum, siginfo_t *info, void *ptr);


struct sigaction act;
int processes;
pid_t *pidfor_signal;

int main(int argc, char *argv[])
{

	//fprintf(stderr, "getting num proc\n");
	processes = get_arguments(argc, argv);


	//fprintf(stderr, "making pipe arrays\n");
	int toSort[processes][2];
	int fromSort[processes][2];
	pid_t pids[processes];
	pidfor_signal = pids;

	/* Setting up signal handling */
	//fprintf(stderr, "setting up signal\n");
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = signalHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL );
	sigaction(SIGQUIT, &act, NULL );
	sigaction(SIGHUP, &act, NULL );


	//fprintf(stderr, "creating pipes\n");
	create_pipe(processes, toSort, fromSort);

	//fprintf(stderr, "sorting\n");
	sorter(processes, pidfor_signal, toSort, fromSort);

	//fprintf(stderr, "suppress\n");
	suppress(processes, toSort, fromSort);

	//fprintf(stderr, "parsing\n");
	parser(processes, toSort, fromSort);

	//fprintf(stderr, "reaping\n");
	reap(processes);

	exit(EXIT_SUCCESS);
}

void reap(int process)
{
	int status;
	for (int i = 0; i < process; i++) {
		wait(&status);
	}
}

void suppressor(int processes, int fds[][2])
{
	std::vector<std::string> temp;
	std::string check, past = " ";
	int valid, lowest, timeout, i;
	FILE **input;

	valid = 1;
	lowest = 0;
	timeout = 0;

	input = (FILE**)calloc(processes, sizeof(FILE*));
	if(input == NULL){
		perror("stream from sort allocation");
		exit(EXIT_FAILURE);
	}

	/* open all the relavent input streams from sorter processes */
	for (i = 0; i < processes; i++){
		input[i] = fdopen(fds[i][0], "r");
	}


	for (i = 0; i < processes; i++){
		temp.push_back(" ");
		read_pipe(i, temp, input, &timeout);
	}

	while(valid && timeout < processes){
		valid = 0;
		check = EXIT_STR;

		for (i = 0; i < processes; i++){
			if(temp[i] != EXIT_STR){
				valid++;
				if (temp[i] < check) {
					check = temp[i];
					lowest = i;
				}
			}
		}
		if ((check != past) && (check != EXIT_STR)) {
			fputs(check.c_str(), stdout);
			past = check;
		}
		read_pipe(lowest, temp, input, &timeout);
	}
	close_file(processes, input);
}

void suppress(int processes, int toSort[][2], int fromSort[][2])
{
	int i;
	switch(fork()){

	case -1: /* error making child */
		perror("error making suppressor child");
		_exit(EXIT_FAILURE);

	case 0: /* child created */
		/* Cleanup all copies of unneeded FDs */
		for ( i = 0; i < processes; i++){
			close(toSort[i][0]);
			close(toSort[i][1]);
			close(fromSort[i][1]);
		}
		/* Suppress now */
		suppressor(processes, fromSort);
		_exit(EXIT_SUCCESS);

	default: /* Parent stuff */
		break;

	}
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
		if (process_number == 0){
			fprintf(stderr,  "Usage: uniqify -[number > 0]\n");
			exit(EXIT_FAILURE);
		}
	}
	return process_number;
}

void create_pipe(int processes, int toSort[][2], int fromSort[][2])
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

void sorter(int processes, pid_t *pids, int toSort[][2], int fromSort[][2])
{

	int i, j;

	for (i = 0; i < processes; i++) {
		switch (pids[i] = fork()) {

		case -1: /* Error making shild */
			perror("creating child");
			exit(EXIT_FAILURE);

		case 0: /* Setup child before exec */
			/* Cleanup all unneeded FDs */
			for (j = 0; j < processes; j++) {
				close(toSort[j][1]);
				close(fromSort[j][0]);
				if (j == i) {
					dup2(toSort[j][0], STDIN_FILENO);
					dup2(fromSort[j][1], STDOUT_FILENO);
				} else {
					close(toSort[j][0]);
					close(fromSort[j][1]);
				}
			}
			execlp("sort", "sort", (char*) NULL);

		default:
			break;
		}
	}
}

void parser(int processes, int toSort[][2], int fromSort[][2])
{

	FILE **output;
	char word[MAX_STR_LEN];
	int i;

	output = (FILE**) calloc(processes, sizeof(FILE*));

	if (output == NULL) {
		perror("file stream allocation");
		exit(EXIT_FAILURE);
	}

	/* close unneeded FDs and end of pipes */
	for (i = 0; i < processes; i++) {
		close(toSort[i][0]);
		close(fromSort[i][0]);
		close(fromSort[i][1]);
		output[i] = fdopen(toSort[i][1], "w");
	}

	/* read words from stdin and put it to sorter */
	i = 0;
	while (get_word(word) != EOF) {
		fputs(word, output[i]);
		if(i == processes - 1){
			i = 0;
		} else {
			i++;
		}
	}
	/* Cleanup of input streams to sort */
	close_file(processes, output);
}

int get_word(char *word)
{

	int read;
	if ((read = fscanf(stdin, "%198[A-Za-z]%*[^A-Za-z]", word)) != EOF) {
		strcat(word, "\n");
		to_lower(word);
		return read;
	} else {
		return EOF;
	}
}

void read_pipe(int position, std::vector<std::string> &temp, FILE **input,
                int *timeout)
{

	char word[MAX_STR_LEN];

	if (!feof(input[position]) &&
	    !ferror(input[position]) &&
	     fgets(word, MAX_STR_LEN, (input[position])) != NULL) {
		temp[position] = word;
	} else {
		++(*timeout);
		temp[position] = EXIT_STR;
	}
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
		kill(pidfor_signal[i], SIGKILL);
		wait(&status);
	}
	exit(EXIT_FAILURE);
}
