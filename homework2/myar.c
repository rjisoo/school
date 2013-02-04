
#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ar.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>


int printTable(char *pathname, int verbose);
int octaltoascii(char ascii);
int extract(int argc, char *argv[]);
int append(int argc, char *argv[]);
int delete(int argc, char *argv[]);
int display_usage(void);
int append_reg(int argc, char *argv[]);

#define BUF_SIZE 4096
#define TRUE 1

int main(int argc, char *argv[]) {

	char flag, flagError;

	/* Check to see if enough parameters supplied */
	if (argc < 3) {
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

	/* Otherwise check to see if a valid flag was passed and execute */
	switch (flag){

	case 'A':
		if (argc < 4) {
			display_usage();
		}
		append_reg(argc, argv);
		/* TODO */
		break;

	case 'd':
		if (argc < 4) {
			display_usage();
		}
		delete(argc, argv);
		/* TODO */
		break;

	case 'q':
		if (argc < 4) {
			display_usage();
		}
		append(argc, argv);
		/* TODO */
		break;

	case 't':
		printTable(argv[2], !TRUE);
		break;

	case 'v':
		printTable(argv[2], TRUE);
		break;

	case 'x':
		if (argc < 4) {
			display_usage();
		}
		extract(argc, argv);
		/* TODO */
		break;

	default:
		/* Just to be safe */
		display_usage();
		break;
	}

	return 0;
}



int printTable(char *pathname, int verbose){
	int Fd, openFlags;
	char headerc[SARMAG+1], headers[] = ARMAG;
	openFlags = O_RDONLY;
	struct ar_hdr ar;
	off_t offset;

	headerc[SARMAG] = '\0'; /* needed for strcmp */

	Fd = open(pathname, openFlags);
	if (Fd == -1){
		/* File doesn't exist */
		perror(pathname);
		return 1;
	}

	/* Check to see if it's a valid archive */
	read(Fd, &headerc, SARMAG);
	if (strcmp(headerc, headers) != 0){
		printf("Not a valid archive type!\n");
		return 1;
	}

		lseek(Fd, SARMAG, SEEK_SET); /* Set it to first file name */

		while (read(Fd, &ar, (size_t)sizeof(ar)) == sizeof(ar)){

			//for (int i = 0; i < 16; i++){
				/* remove terminating / */
				//if (ar.ar_name[i] == '/'){
					//ar.ar_name[i] = '\0';
					//break;
				//}
			//}
			int i = 0;
			while (ar.ar_name[i] != '/'){
				printf("%c", ar.ar_name[i]);
				i++;
			}
			if (verbose != TRUE){
				printf("\n");
			} else {
				printf(" 	");
			}
			if (verbose == TRUE){
				/* Print visual perms */
				octaltoascii(ar.ar_mode[3]);
				octaltoascii(ar.ar_mode[4]);
				octaltoascii(ar.ar_mode[5]);
				printf(" ");
				/* Print UID and then GID */
				int i = 0;
				while (i < 6){
					printf("%c", ar.ar_uid[i]);
					i++;
				}
				i = 0;
				while (i < 6){
					printf("%c", ar.ar_gid[i]);
					i++;
				}
				/* Print file size */
				i = 0;
				while (i < 10){
					printf("%c", ar.ar_size[i]);
					i++;
				}

				/* Print humanized-time */
				time_t time = (time_t) atol(ar.ar_date);
				printf(" %s", ctime(&time));
			}
			offset = (off_t) atoi(ar.ar_size);
			lseek(Fd, offset, SEEK_CUR);
		}
		if (close(Fd) == -1 ){
			perror("close archive");
		}

	exit(EXIT_SUCCESS);
}

int octaltoascii(char ascii){
	switch(ascii){
	case '0':
		printf("---");
		break;

	case '1':
		printf("--x");
		break;

	case '2':
		printf("-w-");
		break;

	case '3':
		printf("-wx");
		break;

	case '4':
		printf("r--");
		break;

	case '5':
		printf("r-x");
		break;

	case '6':
		printf("rw-");
		break;

	case '7':
		printf("rwx");
		break;

	default:
		printf("There was an error within the system.\n");
		_exit(1);
	}
	return 0;
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

int extract(int argc, char *argv[]) {
	/*
	 * Try to open archive, if not exist, error out
	 *
	 * Scan archive for file 1, then for file 2, etc.
	 * 		if file isn't found, error out for not found
	 *
	 * 	Otherwise if file found, open new file
	 * 		if new file exists -> error out
	 * 		otherwise read archive until offset + file size
	 * 		repeat for file list.
	 */
	int archiveFd;

	/* Open archive */
	archiveFd = open(argv[2],O_RDONLY, 0666);
	if (archiveFd == -1){
		perror("archive");
	}

	close(archiveFd);
	return 0;
}

int append(int argc, char *argv[]){
	/*
	 * Check if archive exists
	 * if archive exists, read first SARMAG bytes, compare to ARMAG.
	 * if !=, report not archive error
	 *
	 * Otherwise move past first SARMAG bytes and begin copying.
	 *
	 * If archive doesn't exists, create it, error if not possible.
	 * Write ARMAG to first SARMAG bytes.
	 *
	 * Open subsequent files, error if not possible.
	 * 	-> get file info from stat(), copy to ar_hdr struct
	 * 	   write to archive until EOF.
	 * 	   UNKONWN: Check to see if EOF needs to be acct for.
	 * 	   close each file and move to next.
	 */
	int archiveFd,i;
	int inputFd[argc - 3];

	/* Open archive without create to check existance */
	archiveFd = open(argv[2], O_RDONLY);
	if(archiveFd == -1){
		/* Check further for existence */
		archiveFd = open(argv[2], O_CREAT | O_RDONLY, 0666);
		if (archiveFd == -1){
			/* no way we can open the archive */
			perror("archive");
		}
	}

	/* Open all the files */
	for (i = 0; i < argc - 3; i++) {
		inputFd[i] = open(argv[i + 3], O_RDONLY);
		if (inputFd[i] == -1) {
			perror(argv[i + 3]);
		}
	}

	for (i = 0; i < argc - 3; i++) {
		close(inputFd[i]);
	}
	close(archiveFd);
	return 0;
}

int delete(int argc, char *argv[]) {
	/*
	 * Check if archive exists, if not error
	 *
	 * Check if archive archive, if not error
	 *
	 *
	 *  	TODO: Make it for least amount of traversing.
	 */
	int archiveFd;

	archiveFd = open(argv[2], O_RDONLY);
	if (archiveFd == -1) {
		perror("archive");
	}
	close(archiveFd);
	return 0;
}

int append_reg(int argc, char *argv[]) {
	/*
	 * Similar to quick append, but for all regular files in pwd.
	 *
	 * TODO: get clarification on if this should accept file names input.
	 */
	int archiveFd;

	archiveFd = open(argv[2], O_RDONLY, 0666);
	if (archiveFd == -1) {
		perror("archive");
	}
	close(archiveFd);
	return 0;
}
