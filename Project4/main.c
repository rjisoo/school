#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <omp.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "simulation.h"
#include "ranf.h"

void *watcherfunc(void *simulation_data);
void *grainGrowthfunc(void *simulation_data);
void *grainDeerfunc(void *simulation_data);
int state_init(struct simulation *s);
int state_update(struct simulation *s);

int main(int argc, char **argv){

  pthread_t watcher, grainGrowth, grainDeer;

  struct simulation s;

  state_init(&s);

  // Spawn off the threads for simulation
  if(pthread_create(&watcher, NULL, watcherfunc, &s)){
    fprintf(stderr, "Error creating watcher thread\n");
  }
  if(pthread_create(&grainGrowth, NULL, grainGrowthfunc, &s)){
    fprintf(stderr, "Error creating grainGrowth thread\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&grainDeer, NULL, grainDeerfunc, &s)){
    fprintf(stderr, "Error creating grainDeer thread\n");
    exit(EXIT_FAILURE);
  }
  //pthread_barrier_wait(&barrier);

  if(pthread_join(watcher, NULL)){
    fprintf(stderr, "Error joining watcher thread\n");
    exit(EXIT_FAILURE);
}

  if(pthread_cancel(grainDeer)) {
    fprintf(stderr, "Error joining grainDeer thread\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_cancel(grainGrowth)) {
    fprintf(stderr, "Error joining grainGrowth thread\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

void *watcherfunc(void *simulation_data){

  struct simulation* s = (struct simulation *)simulation_data;

  for(; s->NowYear < 2020;){
    fprintf(stderr, "Month: %d, Year: %d\n", s->NowMonth, s->NowYear);
    fprintf(stderr, "watcher doneAssign\n");
    pthread_barrier_wait(&s->doneAssign);

    s->NowMonth = (s->NowMonth + 1) % 12;

    if(s->NowMonth %12 == 0){
      s->NowYear++;
    }

    state_update(s);

    fprintf(stderr, "watcher donePrint\n");
    pthread_barrier_wait(&s->donePrint);
  }

  return 0;
}

void *grainGrowthfunc(void *simulation_data){

  struct simulation* s = (struct simulation *)simulation_data;

  fprintf(stderr, "Running grainGrowth thread\n");

  for(;;){

    fprintf(stderr, "grainGrowth doneCompute\n");
    pthread_barrier_wait(&s->doneCompute);

    fprintf(stderr, "grainGrowth doneAssign\n");
    pthread_barrier_wait(&s->doneAssign);

    fprintf(stderr, "grainGrowth donePrint\n");
    pthread_barrier_wait(&s->donePrint);

  }

  return 0;
}

void *grainDeerfunc(void *simulation_data){

  struct simulation* s = (struct simulation *)simulation_data;

  fprintf(stderr, "Running grainDeer thread\n");

  for(;;){

    fprintf(stderr, "grainDeer doneCompute\n");
    pthread_barrier_wait(&s->doneCompute);

    fprintf(stderr, "grainDeer doneAssign\n");
    pthread_barrier_wait(&s->doneAssign);

    fprintf(stderr, "grainDeer donePrint\n");
    pthread_barrier_wait(&s->donePrint);

  }

  return 0;
}

int state_init(struct simulation *s){

  s->NowNumDeer =  1;
  s->NowHeight =  1.;
  s->NowMonth =    0;
  s->NowYear  = 2014;

  s->ang = (30.*(float)s->NowMonth + 15.) * (M_PI / 180.);

  s->temp = AVG_TEMP - AMP_TEMP * cos(s->ang);
  s->NowTemp = s->temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

  s->precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(s->ang);
  s->NowPrecip = s->precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
  if(s->NowPrecip < 0.){
    s->NowPrecip = 0.;
  }

  // Init the barriers
  pthread_barrier_init(&s->doneCompute, NULL, 2);
  pthread_barrier_init(&s->doneAssign, NULL, 3);
  pthread_barrier_init(&s->donePrint, NULL, 3);

  return 0;
}

int state_update(struct simulation *s){

  s->ang = (30.*(float)s->NowMonth + 15.) * (M_PI / 180.);

  s->temp = AVG_TEMP - AMP_TEMP * cos(s->ang);
  s->NowTemp = s->temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

  s->precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(s->ang);
  s->NowPrecip = s->precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
  if(s->NowPrecip < 0.){
    s->NowPrecip = 0.;
  }

  return 0;
}