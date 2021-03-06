#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include "errorcodes.h"

#include <CL/cl.h>
#include <CL/cl_platform.h>

#ifndef GLOBAL
#define GLOBAL 8192
#endif

#ifndef LOCAL
#define LOCAL 32
#endif


const int			NUM_ELEMENTS = GLOBAL*1024;
const int			LOCAL_SIZE   = LOCAL;
const char *		CL_FILE_NAME = { "first.cl" };
const float			TOL = 0.50f;

int
main( int argc, char *argv[ ] )
{
	// see if we can even open the opencl kernel program
	// (no point going on if we can't):

	FILE *fp;
#ifdef WIN32
	errno_t err = fopen_s( &fp, CL_FILE_NAME, "r" );
	if( err != 0 )
#else
	fp = fopen( CL_FILE_NAME, "r" );
	if( fp == NULL )
#endif
	{
		fprintf( stderr, "Cannot open OpenCL source file '%s'\n", CL_FILE_NAME );
		return 1;
	}

	// 2. allocate the host memory buffers:

	size_t numWorkGroups = NUM_ELEMENTS / LOCAL_SIZE;

	float *hA = new float[ NUM_ELEMENTS ];
	float *hB = new float[ NUM_ELEMENTS ];
	float *hC = new float[ numWorkGroups ];

	size_t abSize = NUM_ELEMENTS * sizeof(float);
	size_t csize = numWorkGroups * sizeof(float);
	// fill the host memory buffers:

	for( int i = 0; i < NUM_ELEMENTS; i++ )
	{
		hA[i] = hB[i] = sqrt(  (float)i  );
	}

	size_t dataSize = NUM_ELEMENTS * sizeof(float);

	cl_int status;		// returned status from opencl calls
						// test against CL_SUCCESS

	// get the platform id:

	cl_platform_id platform;
	status = clGetPlatformIDs( 1, &platform, NULL );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clGetPlatformIDs failed (2)\n" );
		PrintCLError(status);
	}

	// get the device id:

	cl_device_id device;
	status = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clGetDeviceIDs failed (2)\n" );
		PrintCLError(status);
	}

	// 3. create an opencl context:

	cl_context context = clCreateContext( NULL, 1, &device, NULL, NULL, &status );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clCreateContext failed\n" );
		PrintCLError(status);
	}

	// 4. create an opencl command queue:

	cl_command_queue cmdQueue = clCreateCommandQueue( context, device, 0, &status );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clCreateCommandQueue failed\n" );
		PrintCLError(status);
	}

	// 5. allocate the device memory buffers:

	cl_mem dA = clCreateBuffer( context, CL_MEM_READ_ONLY,  abSize, NULL, &status );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clCreateBuffer failed (1)\n" );
		PrintCLError(status);
	}

	cl_mem dB = clCreateBuffer( context, CL_MEM_READ_ONLY,  abSize, NULL, &status );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clCreateBuffer failed (2)\n" );
		PrintCLError(status);
	}

	cl_mem dC = clCreateBuffer( context, CL_MEM_WRITE_ONLY, csize, NULL, &status );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clCreateBuffer failed (3)\n" );
		PrintCLError(status);
	}

	// 6. enqueue the 2 commands to write the data from the host buffers to the device buffers:

	status = clEnqueueWriteBuffer( cmdQueue, dA, CL_FALSE, 0, abSize, hA, 0, NULL, NULL );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clEnqueueWriteBuffer failed (1)\n" );
		PrintCLError(status);
	}

	status = clEnqueueWriteBuffer( cmdQueue, dB, CL_FALSE, 0, abSize, hB, 0, NULL, NULL );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clEnqueueWriteBuffer failed (2)\n" );
		PrintCLError(status);
	}

	// 7. read the kernel code from a file:

	fseek( fp, 0, SEEK_END );
	size_t fileSize = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	char *clProgramText = new char[ fileSize+1 ];		// leave room for '\0'
	size_t n = fread( clProgramText, 1, fileSize, fp );
	clProgramText[fileSize] = '\0';
	fclose( fp );
	if( n != fileSize )
		fprintf( stderr, "Expected to read %lu bytes read from '%s' -- actually read %lu.\n", fileSize, CL_FILE_NAME, n );

	// create the text for the kernel program:

	char *strings[1];
	strings[0] = clProgramText;
	cl_program program = clCreateProgramWithSource( context, 1, (const char **)strings, NULL, &status );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clCreateProgramWithSource failed\n" );
		PrintCLError(status);
	}
	delete [ ] clProgramText;

	// 8. compile and link the kernel code:

	char *options = { "" };
	status = clBuildProgram( program, 1, &device, options, NULL, NULL );
	if( status != CL_SUCCESS )
	{
		size_t size;
		clGetProgramBuildInfo( program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &size );
		cl_char *log = new cl_char[ size ];
		clGetProgramBuildInfo( program, device, CL_PROGRAM_BUILD_LOG, size, log, NULL );
		fprintf( stderr, "clBuildProgram failed:\n%s\n", log );
		delete [ ] log;
	}

	// 9. create the kernel object:

	cl_kernel kernel = clCreateKernel( program, "ArrayMultReduce", &status );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clCreateKernel failed\n" );
		PrintCLError(status);
	}

	// 10. setup the arguments to the kernel object:

	status = clSetKernelArg( kernel, 0, sizeof(cl_mem), &dA );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clSetKernelArg failed (1) %d\n", status);
		PrintCLError(status);
	}

	status = clSetKernelArg( kernel, 1, sizeof(cl_mem), &dB );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clSetKernelArg failed (2) %d\n", status);
		PrintCLError(status);
	}

	status = clSetKernelArg( kernel, 2, sizeof(float), NULL );
	if( status != CL_SUCCESS ){
		fprintf( stderr, "clSetKernelArg failed (3) %d\n", status);
		PrintCLError(status);
	}

	status = clSetKernelArg( kernel, 3, sizeof(cl_mem), &dC);
	if( status != CL_SUCCESS ){
		fprintf(stderr, "clSetKernelArg failed (4) %d\n", status);
		PrintCLError(status);
	}


	// 11. enqueue the kernel object for execution:

	size_t globalWorkSize[3] = { NUM_ELEMENTS, 1, 1 };
	size_t localWorkSize[3]  = { LOCAL_SIZE,   1, 1 };

	status = clEnqueueBarrier( cmdQueue );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clEnqueueBarrier (1) failed: %d\n", status );

	double time0 = omp_get_wtime( );

	status = clEnqueueNDRangeKernel( cmdQueue, kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clEnqueueNDRangeKernel failed: %d\n", status );

	status = clEnqueueBarrier( cmdQueue );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clEnqueueBarrier (2) failed: %d\n", status );

	double time1 = omp_get_wtime( );

	// 12. read the results buffer back from the device to the host:

	status = clEnqueueReadBuffer( cmdQueue, dC, CL_TRUE, 0, csize, hC, 0, NULL, NULL );
	if( status != CL_SUCCESS )
			fprintf( stderr, "clEnqueueReadBuffer failed\n" );

	// did it work?

	float sum = 0;
	for(int i = 0; i < LOCAL_SIZE; i++){
		sum += hC[i];
	}

	/*for( int i = 0; i < NUM_ELEMENTS; i++ )
	{
		if( fabs( hC[i] - (float)i ) > TOL )
		{
			fprintf( stderr, "%4d: %12.4f * %12.4f wrongly produced %12.4f (%12.4f)\n", i, hA[i], hB[i], hC[i], (float)i );
		}
	}
	*/

	fprintf( stderr, "%8d\t%4d\t%10.3f GigaMultsPerSecond\n", NUM_ELEMENTS, LOCAL_SIZE, (float)NUM_ELEMENTS/(time1-time0)/1000000000. );


	// 13. clean everything up:

	clReleaseKernel(        kernel   );
	clReleaseProgram(       program  );
	clReleaseCommandQueue(  cmdQueue );
	clReleaseMemObject(     dA  );
	clReleaseMemObject(     dB  );
	clReleaseMemObject(     dC  );

	delete [ ] hA;
	delete [ ] hB;
	delete [ ] hC;

	return 0;
}

void PrintCLError( cl_int status)
{
	if( status == CL_SUCCESS )
		return;
	const int numErrorCodes = sizeof( ErrorCodes ) / sizeof( struct errorcode );
	char * meaning = "";
	for( int i = 0; i < numErrorCodes; i++ )
	{
		if( status == ErrorCodes[i].statusCode )
		{
			meaning = ErrorCodes[i].meaning;
			break;
		}
	}

	fprintf( stderr, "%s\n", meaning );
}