#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	void *sb, *sb1, *sb2, *sb3;
	sb = sbrk( sizeof(int) );
	sb1 = sbrk( 1024 * sizeof(int) );
	sb2 = sbrk( 2048 * sizeof(int) );
	sb3 = sbrk( 65536 * sizeof(int) );

	return 0;
}
