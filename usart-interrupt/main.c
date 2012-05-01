#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "usart.h"
#include "wunderboard.h"

int main (void){

	initWunderboard();
	clearArray();
	initializeUSART();
	sei();

	while (1){
		SendStringUSART("This is a test string\r\n");
		setArrayGreen(~PORTC);
		_delay_ms(500);

	}


	return 0;
}
