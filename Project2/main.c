#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <errno.h>
#include "nbodies.h"



int main(int argc, char *argv[ ]){
#ifndef _OPENMP
  fprintf(stderr, "OpenMP is not available\n");
  exit(EXIT_FAILURE);
#endif

  omp_set_num_threads(NUMTHREADS);
  int numProcessors = omp_get_num_procs( );
  fprintf(stderr, "Have %d processors.\n", numProcessors);


  for(int i = 0; i < NUMBODIES; i++){
    Bodies[i].mass = EARTH_MASS  * Ranf( 0.5f, 10.f );
    Bodies[i].x = EARTH_DIAMETER * Ranf( -100.f, 100.f );
    Bodies[i].y = EARTH_DIAMETER * Ranf( -100.f, 100.f );
    Bodies[i].z = EARTH_DIAMETER * Ranf( -100.f, 100.f );
    Bodies[i].vx = Ranf( -100.f, 100.f );;
    Bodies[i].vy = Ranf( -100.f, 100.f );;
    Bodies[i].vz = Ranf( -100.f, 100.f );;
  };

  double time0 = omp_get_wtime( );

  for(int t = 0; t < NUMSTEPS; t++){
    for(int i = 0; i < NUMBODIES; i++){
      float fx = 0.;
      float fy = 0.;
      float fz = 0.;
      Body *bi = &Bodies[i];
      for(int j = 0; j < NUMBODIES; j++){
        if( j == i )    continue;

        Body *bj = &Bodies[j];

        float rsqd = GetDistanceSquared( bi, bj );
        if( rsqd > 0. ){
          float f = G * bi->mass * bj->mass / rsqd;
          float ux, uy, uz;
          GetUnitVector( bi, bj,   &ux, &uy, &uz );
          fx += f * ux;
          fy += f * uy;
          fz += f * uz;
        }
      }

      float ax = fx / Bodies[i].mass;
      float ay = fy / Bodies[i].mass;
      float az = fz / Bodies[i].mass;

      Bodies[i].xnew = Bodies[i].x + Bodies[i].vx*TIMESTEP + 0.5*ax*TIMESTEP*TIMESTEP;
      Bodies[i].ynew = Bodies[i].y + Bodies[i].vy*TIMESTEP + 0.5*ay*TIMESTEP*TIMESTEP;
      Bodies[i].znew = Bodies[i].z + Bodies[i].vz*TIMESTEP + 0.5*az*TIMESTEP*TIMESTEP;

      Bodies[i].vxnew = Bodies[i].vx + ax*TIMESTEP;
      Bodies[i].vynew = Bodies[i].vy + ay*TIMESTEP;
      Bodies[i].vznew = Bodies[i].vz + az*TIMESTEP;
    }

    // setup the state for the next animation step:

    for(int i = 0; i < NUMBODIES; i++){
      Bodies[i].x = Bodies[i].xnew;
      Bodies[i].y = Bodies[i].ynew;
      Bodies[i].z = Bodies[i].znew;
      Bodies[i].vx = Bodies[i].vxnew;
      Bodies[i].vy = Bodies[i].vynew;
      Bodies[i].vz = Bodies[i].vznew;
    }


  }  // t

  double time1 = omp_get_wtime();

  // print performance here:::

  exit(EXIT_SUCCESS);
}


float GetDistanceSquared(Body *bi, Body *bj){
  float dx = bi->x - bj->x;
  float dy = bi->y - bj->y;
  float dz = bi->z - bj->z;
  return dx*dx + dy*dy + dz*dz;
}


float GetUnitVector(Body *from, Body *to, float *ux, float *uy, float *uz){
  float dx = to->x - from->x;
  float dy = to->y - from->y;
  float dz = to->z - from->z;

  float d = sqrt( dx*dx + dy*dy + dz*dz );
  if(d > 0.){
    dx /= d;
    dy /= d;
    dz /= d;
  }

  *ux = dx;
  *uy = dy;
  *uz = dz;

  return d;
}


float Ranf(float low, float high){
  float r = (float) rand();       // 0 - RAND_MAX
  return(low + r * (high - low)/(float)RAND_MAX);
}


/*int Ranf(int ilow, int ihigh){
    float low = (float)ilow;
    float high = (float)ihigh + 0.9999f;

    return (int)(Ranf(low, high));
}*/
