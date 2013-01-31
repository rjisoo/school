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
 * 		-a and -A do not check to see if a chosen file name exist in the archive
 *
 * 		-x and -d operate on first file matched in archive.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {


	return 0;
}

