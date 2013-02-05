
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
#include <fcntl.h>
#include <libgen.h>
#include <stdint.h>


int printTable(char *pathname, int verbose);
int octaltoascii(char ascii);
int extract(int argc, char *argv[]);
int append(int argc, char *argv[]);
int delete(int argc, char *argv[]);
int display_usage(void);
int append_reg(int argc, char *argv[]);
int check_archive(int Fd);

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
		_exit(EXIT_FAILURE);
		return 1;
	}

	/* Check to see if it's a valid archive */
	read(Fd, &headerc, SARMAG);
	if (strcmp(headerc, headers) != 0){
		printf("Not a valid archive type!\n");
		_exit(EXIT_FAILURE);
		return 1;
	}

		lseek(Fd, SARMAG, SEEK_SET); /* Set it to first file name */

		while (read(Fd, &ar, (size_t)sizeof(ar)) == sizeof(ar)){

			int i = 0;
			while (ar.ar_name[i] != '/'){
				printf("%c", ar.ar_name[i]);
				i++;
			}
			if (verbose != TRUE){
				printf("\n");
			} else {
				printf(" 		");
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
			_exit(EXIT_FAILURE);
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
		_exit(EXIT_FAILURE);
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
	_exit(EXIT_FAILURE);


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
		_exit(EXIT_FAILURE);
	}
	check_archive(archiveFd);

	close(archiveFd);
	return 0;
}

int append(int argc, char *argv[]){
	/*
	 * Open archive file
	 */
	int archiveFd, openFlags, i, fileFd, numread;
	struct stat sb;
	struct ar_hdr ar;
	char ar_header[] = ARMAG;
	char buf[BUF_SIZE];

	openFlags = O_CREAT | O_RDWR;

	archiveFd = open(argv[2],openFlags, 0666);
	if (archiveFd == -1){
		perror(argv[2]);
		_exit(EXIT_FAILURE);
	}

	if (stat(argv[2], &sb) == -1){
		perror(argv[2]);
		_exit(EXIT_FAILURE);
	}
	if ((long long)sb.st_size > 0){
		/* Existing file */
		check_archive(archiveFd);

	} else {
		/* new file, write ARMAG */
		write(archiveFd, ar_header, SARMAG);

	}
	/* we have a valid archive file, write passed files to archive */
	/* Go through and open all files to*/
	for (i = 0; i < argc - 3; i++){
		if(stat(argv[i+3], &sb) == -1){
			perror(argv[i+3]);
			unlink(argv[2]);
			_exit(EXIT_FAILURE);
		}
	}
	/* set to always append to end of file */
	lseek(archiveFd, 0, SEEK_END);
	/* all files passed exist */
	for (i = 0; i < argc - 3; i++){
		fileFd = open(argv[i+3], O_RDONLY);
		if (fileFd == -1){
			perror(argv[i+3]);
			unlink(argv[2]);
			_exit(EXIT_FAILURE);
		}
		stat(argv[i+3], &sb);
		sprintf(ar.ar_name, "%-16.16s", basename(argv[i+3]));
		sprintf(ar.ar_date, "%-12u", (uint32_t)sb.st_mtime);
		sprintf(ar.ar_uid, "%-6u", (uint32_t) sb.st_uid);
		sprintf(ar.ar_gid, "%-6u", (uint32_t) sb.st_gid);
		sprintf(ar.ar_mode, "%-8o", (uint32_t) sb.st_mode);
		sprintf(ar.ar_size, "%-10u", (uint32_t) sb.st_size);
		sprintf(ar.ar_fmag, "%s", ARFMAG);


		write(archiveFd, (char*) &ar, sizeof(ar));

		numread = 0;
		/* Read input file */
		while((numread = read(fileFd, buf, BUF_SIZE)) > 0){
			write(archiveFd, buf, numread);
		}
		close(fileFd);
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
		_exit(EXIT_FAILURE);
	}

	check_archive(archiveFd);

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
		_exit(EXIT_FAILURE);
	}

	check_archive(archiveFd);

	close(archiveFd);
	return 0;
}

int check_archive(int Fd){
	/* Checks first SARMAG bytes of a file to see if it's an archive type */
	char ar_header[] = ARMAG;
	char ar_test[SARMAG + 1];
	ar_test[SARMAG] = '\0'; /* NULL termination accounting */
	if (read(Fd,ar_test, SARMAG) == -1){
		perror("read");
		_exit(EXIT_FAILURE);
	}

	if (strcmp(ar_header, ar_test) != 0){
		printf("Not a valid archive\n");
		_exit(EXIT_FAILURE);
	}

	return 0;
}
