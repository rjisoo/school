#ifndef INTEGRATION_H
#define INTEGRATION_H

#define XMIN	 0.
#define XMAX	 3.
#define YMIN	 0.
#define YMAX	 3.

#define Z00	0.
#define Z10	1.
#define Z20	0.
#define Z30	0.

#define Z01	1.
#define Z11	6.
#define Z21	1.
#define Z31	0.

#define Z02	0.
#define Z12	1.
#define Z22	0.
#define Z32	4.

#define Z03	3.
#define Z13	2.
#define Z23	3.
#define Z33	3.

void usage(void);
double Height(long iu, long iv);

#endif /* INTEGRATION_H */
