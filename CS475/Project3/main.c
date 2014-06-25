#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <errno.h>

//#define NUM 0
//#define NUMT 2

struct s{
  float value;
  int pad[NUM]; // fix #1
} Array[4];

int main(int argc, char **argv){

  omp_set_num_threads(NUMT);

  int someBigNumber = 1000000000;
  double time0, time1;

  time0 = omp_get_wtime();

  #pragma omp parallel for
  for(int i = 0; i < 4; i++){
#ifdef FIX2
    volatile float   tmp = Array[i].value; // fix #2, comment out for fix #1.
#endif
    for(int j = 0; j < someBigNumber; j++){
#ifdef FIX2
      tmp += 2.;
#else
      Array[i].value = Array[i].value + 2.;
#endif
    }
  }

  time1 = omp_get_wtime();

  printf("NUM=%d, NUMT=%d, TIME=%f\n", NUM, NUMT, time1-time0);

  exit(EXIT_SUCCESS);
}
