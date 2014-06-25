#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <omp.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include "simulation.h"
#include "ranf.h"

void *watcherfunc(void *simulation_data);
void *grainGrowthfunc(void *simulation_data);
void *grainDeerfunc(void *simulation_data);
int state_init(struct simulation *s);
int state_update(struct simulation *s);
double tempFactor(double factor);
double precipFactor(double factor);

int main(int argc, char **argv){

  pthread_t watcher, grainGrowth, grainDeer, mold;

  struct simulation s;

  state_init(&s);

  srand(time(NULL));

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

    pthread_barrier_wait(&s->doneAssign);

    fprintf(stderr, "%d-%d, %f, %f, %f, %d, %f\n", s->NowYear, s->NowMonth, s->precip, s->temp, s->NowHeight, s->NowNumDeer, s->mold_loss);


    s->NowMonth = (s->NowMonth + 1) % 12;

    if(s->NowMonth %12 == 0){
      s->NowYear++;
    }

    state_update(s);

    pthread_barrier_wait(&s->donePrint);
  }

  return 0;
}

void *grainGrowthfunc(void *simulation_data){

  struct simulation* s = (struct simulation *)simulation_data;

  float height;
  float temp;
  float precip;
  int numdeer;
  float mold_factor;
  float mold_loss;

  for(;;){

    // Pull in state to temp values
    height = s->NowHeight;
    temp = s->temp;
    precip = s->precip;
    numdeer = s->NowNumDeer;
    mold_factor = s->mold_factor;
    mold_loss = height * mold_factor;

    // Perform state based computations
    height += tempFactor(temp) * precipFactor(precip) * GRAIN_GROWS_PER_MONTH;
    height -= (float)numdeer * ONE_DEER_EATS_PER_MONTH;
    height -= mold_factor;

    // Clamp height to zero
    if(height < 0.){
      height = 0.;
    }

    pthread_barrier_wait(&s->doneCompute);

    // Update state values
    s->NowHeight = height;
    s->mold_loss = mold_loss;

    pthread_barrier_wait(&s->doneAssign);

    pthread_barrier_wait(&s->donePrint);

  }

  return 0;
}

void *grainDeerfunc(void *simulation_data){

  struct simulation* s = (struct simulation *)simulation_data;

  int height;
  int numdeer;

  for(;;){

    // Read state into temp values
    height = (int)s->NowHeight;
    numdeer = s->NowNumDeer;

    // Perform state based computations
    if(height > numdeer){
      numdeer++;
    } else if(height < numdeer) {
      numdeer--;
    }

    pthread_barrier_wait(&s->doneCompute);

    // Update state values
    s->NowNumDeer = numdeer;

    pthread_barrier_wait(&s->doneAssign);

    pthread_barrier_wait(&s->donePrint);

  }

  return 0;
}

void *grainMoldfunc(void *simulation_data){
  struct simulation* s = (struct simulation *)simulation_data;

  float temp, precip;
  float loss_factor;

  for(;;){
    temp - s->temp;
    precip = s->precip;
    if(temp > 45 && precip > 6){
      loss_factor = 0.2;
    } else {
      loss_factor = 0.1;
    }

  pthread_barrier_wait(&s->doneCompute);

  s->mold_factor = loss_factor;
  pthread_barrier_wait(&s->doneAssign);
  pthread_barrier_wait(&s->donePrint);

  }

  return 0;
}

int state_init(struct simulation *s){

  s->NowNumDeer =     1;
  s->NowHeight =     1.;
  s->NowMonth =       0;
  s->NowYear  =    2014;
  s->mold_factor =  0.1;
  s->mold_loss =     0.;

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

double tempFactor(double factor){

  return exp(-pow((factor - MIDTEMP)/10., 2.));
}

double precipFactor(double factor){

  return exp(-pow((factor - MIDPRECIP)/10., 2.));
}