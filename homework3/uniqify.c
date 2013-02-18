#define _POSIX_C_SOURCE 199309

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

pid_t *pids; /* These need to be here global for use with the signal handler */
int process_num;
struct sigaction act;

void signalHandler(int signum, siginfo_t *info, void *ptr);
int input_validation(int argc, char *argv[]);
int parser(FILE *input, FILE *output);
int reader(FILE *to, FILE *from);
static char *to_lower(char *str);
void display_error(void);

int main(int argc, char *argv[])
{
	/* Variables */
	int i, exit_num;
	char mem_err[] = "Memory allocation failed";
	char stream_err[] = "Stream allocation failed";

	int **pipefdin, **pipefdout; /* for piping/plumbing to sort */
	FILE **input, **output; /* for giving/getting data to/from sort */

	int pipeToSuppress[2], pipeFromSuppress[2]; /* Pipes to/from suppressor */
	FILE *toSuppress, *fromSuppress; /* Stream to/from suppressor */

	pid_t suppressor;

	/* Setting up signal handling */
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = signalHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL );
	sigaction(SIGQUIT, &act, NULL );
	sigaction(SIGHUP, &act, NULL );

	/* This makes exiting the piping, forking, and plumbing section cleaner */
	exit_num = EXIT_SUCCESS;

	process_num = input_validation(argc, argv);

	/* allocate pipes holding pipes */
	pipefdin = (int**) calloc(process_num, sizeof(int*));
	pipefdout = (int**) calloc(process_num, sizeof(int*));
	if (pipefdin == NULL || pipefdout == NULL ) {
		fprintf(stderr, "%s\n", mem_err);
		exit(EXIT_FAILURE);
	}
	/* Allocate pipes */
	for (i = 0; i < process_num; i++) {
		pipefdin[i] = (int*) calloc(2, sizeof(int));
		pipefdout[i] = (int*) calloc(2, sizeof(int));
		if (pipefdin[i] == NULL || pipefdout[i] == NULL ) {
			fprintf(stderr, "%s\n", mem_err);
			free(pipefdout);
			free(pipefdin);
			exit(EXIT_FAILURE);
		}
	}

	/* allocate file streams */
	input = (FILE**) calloc(process_num, sizeof(FILE*));
	output = (FILE**) calloc(process_num, sizeof(FILE*));
	if (input == NULL || output == NULL ) {
		fprintf(stderr, "%s\n", stream_err);
		free(input);
		free(output);
		free(pipefdin);
		free(pipefdout);
		exit(EXIT_FAILURE);
	}

	/* Allocate holder for PIDs */
	pids = (pid_t*) calloc(process_num, sizeof(pid_t));

	/* pipe and plumb */
	for (i = 0; i < process_num; i++) {
		if (pipe(pipefdin[i]) == -1 || pipe(pipefdout[i]) == -1) {
			perror("sort pipes");
			exit(EXIT_FAILURE);
		}

		/* Create processes (fork) */
		switch (pids[i] = fork()) {

		case -1:
			/* error */
			perror("process not created");
			exit(EXIT_FAILURE);

		case 0:
			/* Child stuff and plumbing */
			/* close sort write fd */
			if (close(pipefdout[i][1]) == -1) {
				perror("close sort in write");
				_exit(EXIT_FAILURE);
			}
			/* close sort out's read fd */
			if (close(pipefdin[i][0]) == -1) {
				perror("close sort out read");
				_exit(EXIT_FAILURE);
			}
			/* set sort in as parent out */
			if (dup2(pipefdout[i][0], STDIN_FILENO) == -1) {
				perror("mapping sort stdin");
				_exit(EXIT_FAILURE);
			}
			/* set sort out as output */
			if (dup2(pipefdin[i][1], STDOUT_FILENO) == -1) {
				perror("mapping sort stdout");
				_exit(EXIT_FAILURE);
			}
			/* close it's remapped fd */
			if (close(pipefdout[i][0]) == -1) {
				perror("closing sort unused pipe in from remap");
				_exit(EXIT_FAILURE);
			}
			/* close it's remapped fd */
			if (close(pipefdin[i][1]) == -1) {
				perror(
				                "closing sort unused pipe out from remap");
				_exit(EXIT_FAILURE);
			}
			execlp("sort", "sort", (char *) NULL );
			break;

		default:
			/* Parent stuff and plumbing */
			output[i] = fdopen(pipefdout[i][1], "w");
			input[i] = fdopen(pipefdin[i][0], "r");
			if(output[i] == NULL || input[i] == NULL){
				perror("stream to sort");
				exit(EXIT_FAILURE);
			}
			if(close(pipefdout[i][0]) == -1){
				perror("closing sort unneeded fd");
				exit(EXIT_FAILURE);
			}
			if(close(pipefdin[i][1]) == -1){
				perror("closing unneeded fd");
				exit(EXIT_FAILURE);
			}
			break;
		}
	}

	/* Parse input from stdin to sort */
	i = 0;
	while (parser(stdin, output[i]) != EOF) {
		if (i + 1 == process_num) {
			i = 0;
		} else {
			i++;
		}
	}
	fclose(stdin);
	for (i = 0; i < process_num; i++) {
		fclose(output[i]);
	}

	/* Pipe and plumb the suppressor process */

	/* Read from sorters round-robin, and suppress (for now, print to stdout) */

	i = 0;
	while (reader(stdout, input[i]) != EOF) {
		if (i + 1 == process_num) {
			i = 0;
		} else {
			i++;
		}
	}

	for (i = 0; i < process_num; i++) {
		fclose(input[i]);
	}
	free(input);
	free(output);
	free(pipefdin);
	free(pipefdout);
	exit(exit_num);
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{
	int status, i;
	//printf("\nSignal: %d\n", signum);
	//kill(pids[0], signum);
	//wait(&status);
	for (i = 0; i < process_num; i++) {
		kill(pids[i], SIGKILL);
		wait(&status);
	}
	exit(EXIT_FAILURE);
}

int input_validation(int argc, char *argv[])
{
	int process_num;
	/* Check that only number of processes is passed as argument */
	if (argc < 2 || argc > 2) {
		display_error();
		exit(EXIT_FAILURE);
	}

	/* Read in the number of processes wanted */
	sscanf(argv[1] + 1, "%d", &process_num); /* sneaky pointer math to remove - */
	if (process_num == 0) {
		display_error();
		exit(EXIT_FAILURE);
	} else if (process_num > sysconf(_SC_CHILD_MAX)) { /* sanity check */
		fprintf(stderr, "Sorry, %d is too large for this system\n",
		                process_num);
		exit(EXIT_FAILURE);
	}
	return process_num;
}

int parser(FILE *input, FILE *output)
{
	char buffer[200];
	int read;

	read = (fscanf(input, "%*[^A-Za-z']"), fscanf(input, "%198[A-Za-z']",
	                buffer));

	if (read != EOF) {
		strcat(buffer, "\n");
		fputs(to_lower(buffer), output);
		return read;
	} else {
		return EOF;
	}
}



int reader(FILE *to, FILE *from)
{

	char buffer[200];
	if (fgets(buffer, 200, from) == NULL ) {
		return EOF;
	} else {
		fputs(buffer, to);
	}

	return 0;
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

void display_error(void)
{
	char error[] =
	                "Usage: uniqify -[number_of_processes (greater than zero)]";
	fprintf(stderr, "\n %s\n\n\n", error);
}
