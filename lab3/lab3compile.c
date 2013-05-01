#include <stdio.h>
#include <endian.h>

int main(int argc, char **argv)
{
	short val;
	char *p_val;
	p_val = (char *) &val;
	/*
	  The following two lines assume big-endian
	  Architecture to initialize the variable Val
	  to 0x1234.
	*/
#if _BYTE_ORDER == _BIG_ENDIAN
	p_val[1] = 0x12;
	p_val[0] = 0x34;
#else
	p_val[1] = 0x34;
	p_val[0] = 0x12;
#endif

	printf("%x\n", val);

	return 0;
}
