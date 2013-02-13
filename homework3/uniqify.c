#define _POSIX_C_SOURCE 199309

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>

struct sigaction act;

int parser(FILE *input, FILE *output);
static char *to_lower(char *str);
void signalHandler(int signum, siginfo_t *info, void *ptr);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("\n Usage: uniqify -[number_of_processes]\n");
		exit(EXIT_FAILURE);
	}
	int num_proc;
	sscanf(argv[1] + 1, "%d", &num_proc);
	if (num_proc == 0) {
		printf(
		                "\n Usage: uniqify -[number_of_processes (greater than zero)]\n");
		exit(EXIT_FAILURE);
	}
	printf("\nNumber of commands: %d, Number of processes: %d\n", argc,
	                num_proc);
	memset(&act, 0, sizeof(act));

	act.sa_sigaction = signalHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL );
	sigaction(SIGQUIT, &act, NULL );
	sigaction(SIGHUP, &act, NULL );

	while (parser(stdin, stdout) > 0) {
		//sleep(50);
	}

	exit(EXIT_SUCCESS);
}

void signalHandler(int signum, siginfo_t *info, void *ptr)
{
	printf("\nSignal: %d\n", signum);
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
