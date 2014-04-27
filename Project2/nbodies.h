#ifndef NBODIES_H
#define NBODIES_H

// constants:
const double G              = 6.67300e-11;  // m^3 / ( kg s^2 )
const double EARTH_MASS     = 5.9742e24;    // kg
const double EARTH_DIAMETER = 12756000.32;  // meters
const double TIMESTEP       = 1.0;          // secs

#define NUMBODIES    100
#define NUMSTEPS     200

struct body
{
float mass;
  float x, y, z;      // position
  float vx, vy, vz;   // velocity
  float fx, fy, fz;   // forces
  float xnew, ynew, znew;
  float vxnew, vynew, vznew;
};

typedef struct body Body;

// function prototypes:

float GetDistanceSquared(Body *bi, Body *bj);
float GetUnitVector(Body *from, Body *to, float *ux, float *uy, float *uz);
float Ranf(float low, float high);
//int Ranf(int ilow, int ihigh);

Body    Bodies[NUMBODIES];

#endif /* NBODIES_H */