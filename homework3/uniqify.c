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

struct sigaction act;
pid_t pid;

int parser(FILE *input, FILE *output);
static char *to_lower(char *str);
void signalHandler(int signum, siginfo_t *info, void *ptr);

int main(int argc, char *argv[])
{

	int num_proc;
	int pipefdout[2], pipefdin[2];
	FILE *output, *input;

	if (pipe(pipefdout) != 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if (pipe(pipefdin) != 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	/* check if correct number of arguments passed */
	if (argc < 2) {
		printf("\n Usage: uniqify -[number_of_processes]\n");
		exit(EXIT_FAILURE);
	}

	/* read in number of processes desired */
	sscanf(argv[1] + 1, "%d", &num_proc); /* sneaky hack to remove - */
	if (num_proc == 0) {
		printf("\n Usage: uniqify -[number_of_processes (greater than zero)]\n");
		exit(EXIT_FAILURE);
	}
	printf("\nNumber of commands: %d, Number of processes: %d\n", argc,
	                num_proc);

	/* Setting up signal handling */
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = signalHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL );
	sigaction(SIGQUIT, &act, NULL );
	sigaction(SIGHUP, &act, NULL );

	switch(pid = fork()){
	case -1:
		perror("process creation");
		exit(EXIT_FAILURE);
	case 0:
		//child
		close(pipefdout[1]);
		close(pipefdin[0]);
		dup2(pipefdout[0], STDIN_FILENO);
		dup2(pipefdin[1], STDOUT_FILENO);
		close(pipefdout[0]);
		close(pipefdin[1]);
		execlp("sort", "sort", "-u", (char *)NULL);

		break;
	default:
		output = fdopen(pipefdout[1], "w");
		input = fdopen(pipefdin[0], "r");

		close(pipefdout[0]);
		close(pipefdin[1]);
		while(parser(stdin, output) > 0);
		fclose(output);
		while(parser(input, stdout) > 0);
		fclose(input);
		break;
	}


	exit(EXIT_SUCCESS);
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{
	int status;
	//printf("\nSignal: %d\n", signum);
	kill(pid, signum);
	wait(&status);
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
