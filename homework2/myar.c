/*
 * Input:
 * 		myar -[qxtvdA] archive file_list...
 *
 * 		Only accepting 1 flag at a time.
 *
 * 		q: 	quick append to archive
 *
 * 		x: 	extract named files from archive
 *
 * 		t: 	print concise table of contents from archive
 *
 * 		v: 	print verbose table of contents from archive
 *
 * 		d: 	delete files from archive
 *
 * 		A: 	quick append all regular files to archive, excluding archive
 *
 * 		-q creates if archive doesn't exist with permissions 666
 *
 * 		Other commands - report error is file doesn't exist, or in wrong format
 *
 * 		-q and -A do not check to see if a chosen arcive exists
 *
 * 		-x and -d operate on first file matched in archive.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ar.h>
#include <errno.h>

int display_usage(void);

int main(int argc, char *argv[]) {
	/*
	 * Arguments information:
	 * 		myar == 1st arg
	 * 		flag == 2nd arg
	 * 		archive == 3rd arg
	 * 		files to archive == 4+ args
	 */
	char flag;

	/*printf("Number Args: %d\n", argc);*/

	if (argc < 4) {
		printf("Invalid usage of ar!\n");
		display_usage();
	}

	return 0;
}

int display_usage(void) {

	printf(
			"Usage: myar [-OPTION] archive-file files...\n\n"
			"Examples:\n"
			" myar -q archive foo bar  # Create archive from files foo and bar\n"
			" myar -x archive foo bar  # Extract files foo and bar from archive\n"
			" myar -d archive foo bar  # Delete files foo and bard from archive\n\n"
			"Commands:\n"
			" -A 	quickly append all regular files in current directory\n\n"
			" -d 	delete named files form archive\n\n"
			" -q 	quickly append named files to archive\n\n"
			" -t 	print concise table of contents of the archive\n\n"
			" -v 	print verbose table of contents of archive\n\n"
			" -x 	extract named files from archive\n\n");


	return 0;
}

