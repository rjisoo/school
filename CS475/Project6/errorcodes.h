#ifndef ERRORCODESCL_H
#define ERRORCODESCL_H

#include <CL/cl.h>

// the function prototype:
void PrintCLError(cl_int status);

// the function:

struct errorcode
{
  cl_int    statusCode;
  char *    meaning;
};

#endif