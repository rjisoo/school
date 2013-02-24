//#define _POSIX_C_SOURCE 199309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>


int main(int argc, char *argv[])
{

	uint8_t *bitmask;

	bitmask = (uint8_t*)calloc(UINT32_MAX/8, sizeof(uint8_t));
	if(bitmask == NULL){
		perror("memory allocation");
		exit(EXIT_FAILURE);
	}

	sleep(50);

	exit(EXIT_SUCCESS);
}
