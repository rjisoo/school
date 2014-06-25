#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <omp.h>
#include <string.h>
#include "integration.h"

long NUMS;
int NUMT;

int main(int argc, const char* argv[]){

	long i;
	double volume;
	double fullTileArea, time0, time1;

	if(sscanf(argv[2], "%ld", &NUMS) != 1){
		printf("Invalid number steps: %s\n", argv[2]);
		usage();
		exit(EXIT_FAILURE);
	}
	if (sscanf(argv[4], "%d", &NUMT) != 1){
		printf("Invlaid number threads: %s\n", argv[4]);
		usage();
		exit(EXIT_FAILURE);
	}

	fullTileArea = (  ( (XMAX-XMIN)/(double)(NUMS-1) )  *  ( ( YMAX - YMIN )/(double)(NUMS-1) )  );
	volume = 0;

	omp_set_num_threads(NUMT);

	time0 = omp_get_wtime();

	#pragma omp parallel for reduction(+:volume) private(i)
	for(i = 0; i < NUMS*NUMS; i++){
		long iu = i % NUMS;
		long iv = i / NUMS;

		volume += Height(iu, iv) * fullTileArea;
	}

	time1 = omp_get_wtime();

	printf("%f\n", volume);


	exit(EXIT_SUCCESS);
}

void usage(void){
	printf(
			"Usage: integration -n <number> -t <number>\n"
			"Flags:\n"
			"\tn: number of steps\n"
			"\tt: number of threads"
			"\th: help (show this output)\n"
			"\t--help: same as -h\n"
			);
}


double Height(long iu, long iv){

	double u = (double)iu / (double)(NUMS-1);
	double v = (double)iv / (double)(NUMS-1);

	// the basis functions:

	double bu0 = (1.-u) * (1.-u) * (1.-u);
	double bu1 = 3. * u * (1.-u) * (1.-u);
	double bu2 = 3. * u * u * (1.-u);
	double bu3 = u * u * u;

	double bv0 = (1.-v) * (1.-v) * (1.-v);
	double bv1 = 3. * v * (1.-v) * (1.-v);
	double bv2 = 3. * v * v * (1.-v);
	double bv3 = v * v * v;

	// finally, we get to compute something:

	double height = 	  bu0 * ( bv0*Z00 + bv1*Z01 + bv2*Z02 + bv3*Z03 )
			+ bu1 * ( bv0*Z10 + bv1*Z11 + bv2*Z12 + bv3*Z13 )
			+ bu2 * ( bv0*Z20 + bv1*Z21 + bv2*Z22 + bv3*Z23 )
			+ bu3 * ( bv0*Z30 + bv1*Z31 + bv2*Z32 + bv3*Z33 );

	return height;
}
