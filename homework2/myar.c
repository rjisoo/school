
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
int extract(void);
int append(void);
int delete(void);
int display_usage(void);

#define BUF_SIZE 4096
#define TRUE 1

int main(int argc, char *argv[]) {

//	int archiveExist, archiveNew, archiveFd, inputFd, openFlags;
	char flag, flagError;
//	char headerc[SARMAG];
//	char headers[] = ARMAG;
//	mode_t filePerms;
//	ssize_t numRead;

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

	switch (flag){

	case 'A':
		printf("Not yet implemented\n");
		break;

	case 'd':
		printf("Not yet implemented\n");
		break;

	case 'q':
		printf("Not yet implemented\n");
		break;

	case 't':
		printTable(argv[2], !TRUE);
		break;

	case 'v':
		printTable(argv[2], TRUE);

		break;

	case 'x':
		printf("Not yet implemented\n");
		break;

	default:
		display_usage();
		break;
	}

	/* 0666 permissions */
//	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH;
//	openFlags = O_RDONLY;

//	archiveFd = open(argv[2], openFlags, filePerms);
//	if (archiveFd == -1){
//		/* If error, check to see if because file doesn't exist */
//		archiveFd = open(argv[2], openFlags | O_CREAT, filePerms);
//		if (archiveFd == -1){
//			/* There is no way to make the archive file */
//			perror(argv[2]);
//			return 2;
//		} else {

//		}
//	} else {
//		/* check the archive file header to see if archive */
//		read(archiveFd, &headerc, SARMAG);
//		if (strcmp(headerc, headers) != 0){
//			printf("Invalid archive format!\n");
//			_exit(1);
//		} else {
//			archiveExist = archiveFd;
//		}
//	}

	//printTable(argv[2], TRUE);

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
