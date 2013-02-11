#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <malloc.h>
#include <signal.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0
#define MAX_BUF_SIZE 4096

int parser(FILE *input);
static char *to_lower(char *str);

int main(int argc, char *argv[])
{
	int inputfd, num_proc;
	pid_t *pids;
	FILE *inputfile;

	if (argc < 3) {
		printf("%s [number_of_processes] inputfile\n", argv[0]);
	}

	sscanf(argv[1], "%d", &num_proc);

	pids = (pid_t*) calloc(num_proc, sizeof(pid_t));
	if (pids == NULL ) {
		perror("memory");
		exit(EXIT_FAILURE);
	}

	inputfd = open(argv[2], O_RDONLY);
	if (inputfd == -1) {
		perror("input file");
		free(pids);
		exit(EXIT_FAILURE);
	}

	inputfile = fdopen(inputfd, "r");

	parser(inputfile);

	if (fclose(inputfile) != 0) {
		perror("closing input stream");
		free(pids);
		exit(EXIT_FAILURE);
	}

	free(pids);
	exit(EXIT_SUCCESS);
}

int parser(FILE *file)
{
	char buffer[200];

	while (fscanf(file, "%*[^A-Za-z]"), fscanf(file, "%198[a-zA-Z]", buffer)
	                > 0) {
		strcat(buffer, "\n");
		printf("%s", to_lower(buffer));
	}
	return 0;
}

/* ttp://stackoverflow.com/questions/6857445/lowercase-urls-in-varnish-inline-c */
static char *to_lower(char *str)
{
	char *s = str;
	while (*s) {
		if (isupper (*s)) {
			*s = tolower (*s);
		}
		s++;
	}
	return str;
}
