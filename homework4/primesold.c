//#define _POSIX_C_SOURCE 199309

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>

int main(int argc, char * argv[])
{

	long limit = UINT32_MAX;
	long i, j, m;
	long numfound = 0;
	uint8_t *list;

	m = sqrt(limit);

#ifdef DEBUG
	fprintf(stdout, "m is: %ld\n", m);
	fprintf(stdout, "Allocating array for primes\n");
#endif

	list = (uint8_t*) calloc((limit + 1), sizeof(uint8_t));
	if (list == NULL ) {
		fprintf(stderr, "Memory allocation failure\n");
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	fprintf(stdout, "Beginning sieve\n");
#endif

	/* Take care of special numbers */
	list[0] = list[1] = 1;

	for (i = 0; i <= m; i++) {
		if (list[i] == 0) {
			for (j = i * i; j <= limit; j += i) {
				if (list[j] == 0) {
					list[j] = 1;
					numfound++;
				}
			}
		}
	}

	fprintf(stdout, "number of primes found: %ld\n", limit - numfound);

	free(list);
	return 0;
}

