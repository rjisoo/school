/*
 * ##################################################################
 * # Author:        Geoffrey Corey                                  #
 * # Date:          02-08-13                                        #
 * # File:          uniqify.c                                       #
 * # Description:   Takes a text file and separates it into its     #
 * #                unique words and prints them on the screen      #
 * #                using the system's /bin/sort utility.           #
 * ##################################################################
 */

#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0
#define MAX_BUF_SIZE 4096

/*
 * display_usage is the error message printed to the user upon the use of invalid
 * arguments passed to the uniqify program.
 */
int display_usage(void);

/*
 * This program parses the words from the input file to be sent to the sorters
 * and uniqified.
 */
int parser(FILE *input);

int main(int argc, char *argv[]) {

	int inputFd, num_proc;
	FILE *inputFile;

	/* Input verification */
	if (argc < 3) {
		display_usage(); /* invalid number of arguments passed */
	}

	sscanf(argv[1], "%d", &num_proc); /* get num processes */

	/* try to open input file */
	inputFd = open(argv[2], O_RDONLY);
	if (inputFd == -1) {
		perror("Opening input file:");
		exit(EXIT_FAILURE);
	}

	inputFile = fdopen(inputFd, "r"); /* Open input file as a stream */

	parser(inputFile); /* parse input file */


	/* close input file */
	if (fclose(inputFile) != 0) {
		perror("input stream");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

int display_usage(void) {
	printf("\n"
			"uniqify:\n  A parallel sorting process that displays the "
			"unique words contained in a text file.\n\n"
			"Usage:\n  uniqify  [num_processes] inputfile\n"
			"\n"
			"Flags:\n"
			"  -h \tPrintf help message.\n\n");

	exit(EXIT_FAILURE);
}

int parser(FILE *input) {

	char buffer[200];

	while( fscanf(input, "%*[^A-Za-z]"), fscanf(input, "%198[a-zA-Z]", buffer) > 0){
		strcat(buffer, "\n");
		printf("%s", buffer);
	}
	return 0;
}
