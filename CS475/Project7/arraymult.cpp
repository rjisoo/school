#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include "simd.h"

#ifndef NUM
#define NUM 100
#endif

#define TRIALS 10

float Ranf(float, float);
int Ranf(int, int);

int main(int argc, char **argv){

  double time0, time1, simd_avg, n_avg;
  int i;

  //double prec = omp_get_wtick();

  float *a = new float[NUM];
  float *b = new float[NUM];
  float *c = new float[NUM];

  SimdSet(a, Ranf(-10.f, 10.f), NUM);
  SimdSet(b, Ranf(-10.f, 10.f), NUM);

  time0 = Timer();
  for(i = 0; i < TRIALS; i++){
    SimdMul(a, b, c, NUM);
  }
  time1 = Timer();

  simd_avg = (time1 - time0)/(float) TRIALS;

  time0 = Timer();
  for(i = 0; i < TRIALS; i++){
    NonSimdMul(a, b, c, NUM);
  }
  time1 = Timer();

  n_avg = (time1 - time0)/(float) TRIALS;

  fprintf(stderr, "NUM:\t%d \tSIMD:\t%8.3f MFLOPS \tNon-SIMD:\t%8.3f MFLOPS\n", NUM, (float) NUM/simd_avg/1000000.f, (float) NUM/n_avg/1000000.f);
  exit(EXIT_SUCCESS);
}

float Ranf(float low, float high) {
    float r = (float) rand(); // 0 - RAND_MAX
    return ( low + r * (high - low) / (float) RAND_MAX);
}

int Ranf(int ilow, int ihigh) {
    float low = (float) ilow;
    float high = (float) ihigh + 0.9999f;
    return (int) (Ranf(low, high));
}