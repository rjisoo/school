#include <avr/io.h>
#include <stdlib.h>
#include "usart.h"
#include "wunderboard.h"



int main (void){

	initWunderboard();
	clearArray();
	initializeUSART();

	uint8_t string[] = "this is a test\r\n";

	SendStringUSART((uint8_t *) string);

	return 0;
}
