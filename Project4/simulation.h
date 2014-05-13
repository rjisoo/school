#ifndef SIMULATION_H
#define SIMULATION_H

#include <pthread.h>

const float GRAIN_GROWS_PER_MONTH =     8.0;
const float ONE_DEER_EATS_PER_MONTH =   0.5;

const float AVG_PRECIP_PER_MONTH =      6.0;
const float AMP_PRECIP_PER_MONTH =      6.0;
const float RANDOM_PRECIP =             2.0;

const float AVG_TEMP =                  50.0;
const float AMP_TEMP =                  20.0;
const float RANDOM_TEMP =               10.0;

const float MIDTEMP =                   40.0;
const float MIDPRECIP =                 10.0;

struct simulation{
  int   NowYear;        // 2014 - 2019
  int   NowMonth;       // 0 - 11

  float NowPrecip;      // inches of rain per month
  float NowTemp;        // temperature this month
  float NowHeight;      // grain height in inches
  int   NowNumDeer;

  float ang;
  float temp;
  float precip;

  pthread_barrier_t doneCompute;
  pthread_barrier_t doneAssign;
  pthread_barrier_t donePrint;
};

#endif /* SIMULATION_H */
