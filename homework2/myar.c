
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ar.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int display_usage(void);

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
	/*
	 * Arguments information:
	 * 		myar == 1st arg
	 * 		flag == 2nd arg
	 * 		archive == 3rd arg
	 * 		files to archive == 4+ args
	 */
	int archiveFd, inputFd, openFlags;
	char flag, flagError;
	char headerc[SARMAG];
	char headers[] = ARMAG;
	mode_t filePerms;
	ssize_t numRead;

	/* Check to see if enough parameters supplied */
	if (argc < 2) {
		display_usage();
	}

	/* check if flag passed and get it */
	flag = getopt(argc, argv, "Adqtvx");
	if (flag == -1){ /* No flag passed */
		display_usage();
	}

	/* check if more than 1 flag passed */
	flagError = getopt(argc, argv, "Adqtvx");
	if (flagError != -1) { /* There was a wrong flag passed */
		printf("\nInvalid flag: %s\n\n", argv[1]);
		display_usage();
	}

	/* printing table of contents */

	/*
	 * Open archive: 	check to see if exists, if does, open and see if
	 * 				 	it's and archive file type, otherwise report error
	 *
	 * Open files: 		see if file exists, open is exists, otherwise
	 * 					report error.
	 */

	/*switch (flag){

	case 'A':

		break;

	case 'd':

		break;

	case 'q':

		break;

	case 't':

		break;

	case 'v':

		break;

	case 'x':

		break;

	default:
		display_usage();
		break;
	}*/

	/* 0666 permissions */
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH;
	openFlags = O_RDONLY;

	archiveFd = open(argv[2], openFlags, filePerms);
	if (archiveFd == -1){
		/* If error, check to see if creating errors */
		archiveFd = open(argv[2], openFlags | O_CREAT, filePerms);
		if (archiveFd == -1){
			/* There is no way to make the archive file */
			perror(argv[2]);
			return 2;
		}
	} else {
		/* check the archive file header to see if archive */
		read(archiveFd, &headerc, SARMAG);
		if (strcmp(headerc, headers) != 0){
			printf("Invalid archive format!\n");
			_exit(1);
		} else {
			/* do the stuff to the archive */
		}
	}




	return (EXIT_SUCCESS);
}


int display_usage(void) {

	printf(
			"Usage: myar [-OPTION] archive-file files...\n\n"
			"Examples:\n"
			" myar -q archive foo bar  # Create or append archive from files foo and bar\n"
			" myar -x archive foo bar  # Extract files foo and bar from archive\n"
			" myar -d archive foo bar  # Delete files foo and bard from archive\n\n"
			"Commands:\n"
			" -A 	quickly append all regular files in current directory\n\n"
			" -d 	delete named files form archive\n\n"
			" -q 	quickly append named files to archive\n\n"
			" -t 	print concise table of contents of the archive\n\n"
			" -v 	print verbose table of contents of archive\n\n"
			" -x 	extract named files from archive\n\n");
	_exit(1);


	return 0;
}
