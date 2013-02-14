#define _POSIX_C_SOURCE 199309

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <wait.h>
#include <malloc.h>

struct sigaction act;
//int *pid, num_proc; /* This is a global variable for usage with the signal handler */
pid_t *pids;
long num_proc;

int parser(FILE *input, FILE *output);
static char *to_lower(char *str);
void signalHandler(int signum, siginfo_t *info, void *ptr);
void display_error(void);


int main(int argc, char *argv[])
{

	int i; /* The number of processes to run */
	int **pipefdin; /* array of file descriptors for input from sorter */
	int **pipefdout; /* array of file descriptors for output to sorter */
	//int pipefdout[2], pipefdin[2];
	//FILE *output, *input;
	FILE **output;
	FILE **input;
	char mem_err[] = "Memory allocation failure";
	char stream_err[] = "Stream allocation failure";

	/* check if correct number of arguments passed */
	if (argc < 2) {
		display_error();
		exit(EXIT_FAILURE);
	}

	/* read in number of processes desired */
	sscanf(argv[1]+1, "%ld", &num_proc); /* sneaky hack to remove - */
	if (num_proc == 0) {
		display_error();
		exit(EXIT_FAILURE);
	}

	/* Check to see if number of desired processes is greater than the system
	 * allows.
	 */
	if(num_proc > sysconf(_SC_CHILD_MAX)){
		fprintf(stderr, "Sorry, %ld is too large for this system\n", num_proc);
		exit(EXIT_FAILURE);
	}

	/* Allocating array to hold pipe file descriptors */
	pipefdin = (int**)calloc(num_proc, sizeof(int*));
	if(pipefdin == NULL){
		fprintf(stderr, "%s\n", mem_err);
		exit(EXIT_FAILURE);
	}

	pipefdout = (int**) calloc(num_proc, sizeof(int*));
	if (pipefdout == NULL ) {
		fprintf(stderr, "%s\n", mem_err);
		exit(EXIT_FAILURE);
	}

	/* Allocate stream */
	input = (FILE**)calloc(num_proc, sizeof(FILE*));
	if(input == NULL){
		fprintf(stderr, "%s\n", stream_err);
		exit(EXIT_FAILURE);
	}
	output = (FILE**) calloc(num_proc, sizeof(FILE*));
	if (output == NULL ) {
		fprintf(stderr, "%s\n", stream_err);
		exit(EXIT_FAILURE);
	}

	/* Allocate space for pipe file descriptors to store */
	for(i = 0; i < num_proc; i++){
		pipefdout[i] = (int*)calloc(2, sizeof(int));
		if(pipefdout[i] == NULL){
			fprintf(stderr, "%s\n", mem_err);
			exit(EXIT_FAILURE);
		}
		pipefdin[i] = (int*)calloc(2, sizeof(int));
		if(pipefdin[i] == NULL){
			fprintf(stderr, "%s\n", mem_err);
			exit(EXIT_FAILURE);
		}
	}

	/* Allocate array of pids */
	pids = (pid_t*)calloc(num_proc, sizeof(pid_t));


	/* Setting up signal handling */
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = signalHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL );
	sigaction(SIGQUIT, &act, NULL );
	sigaction(SIGHUP, &act, NULL );

	/* Begin piping and forking processes */
	for (i = 0; i < num_proc; i++) {
		if (pipe(pipefdin[i]) == -1) {
			perror("pipes");
			exit(EXIT_FAILURE);
		}
		if (pipe(pipefdout[i]) == -1) {
			perror("pipes");
			exit(EXIT_FAILURE);
		}
		switch (pids[i] = fork()) {
		case -1:
			perror("process not created");
			free(pipefdin);
			free(pipefdout);
			free(input);
			free(output);
			break;

		case 0:
			/* child */
			close(pipefdout[i][1]); /* close sort write fd */
			close(pipefdin[i][0]); /* close sort out's read fd */
			dup2(pipefdout[i][0], STDIN_FILENO); /* set sort in as parent out */
			dup2(pipefdin[i][1], STDOUT_FILENO);/* set sort out as output */
			close(pipefdout[i][0]); /* close it's remapped fd */
			close(pipefdin[i][1]); /* close it's remapped fd */
			execlp("sort", "sort", (char *) NULL );
			break;

		default:
			/* parent */
			output[i] = fdopen(pipefdout[i][1], "w");
			input[i] = fdopen(pipefdin[i][0], "r");

			close(pipefdout[i][0]);
			close(pipefdin[i][1]);
			break;
		}
	}

	//sleep(50);

	/* parse */
	//while (parser(stdin, output[0]) > 0);
	//fclose(output[0]);
	//while (parser(input[0], stdout) > 0);
	//fclose(input[0]);

	/* cleanup the arrays */
	free(pipefdin);
	free(pipefdout);
	free(input);
	free(output);

	exit(EXIT_SUCCESS);
}

void display_error(void)
{
	char error[] = "Usage: uniqify -[number_of_processes (greater than zero)]";
	fprintf(stderr, "\n %s\n\n\n", error);
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{
	int status, i;
	//printf("\nSignal: %d\n", signum);
	//kill(pids[0], signum);
	//wait(&status);
	for(i = 0; i < num_proc; i++){
		kill(pids[i], signum);
		wait(&status);
	}
	exit(EXIT_FAILURE);
}

int parser(FILE *input, FILE *output)
{

	char buffer[200];

	int read;

	read = (fscanf(input, "%*[^A-Za-z]"), fscanf(input, "%198[a-zA-Z]",
	                buffer));

	if (read > 0) {
		strcat(buffer, "\n");
		fprintf(output, "%s", to_lower(buffer));
	}
	return read;
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
