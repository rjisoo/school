/**
 * TODO:
 * 		1. Implement/Test usart receive interrupt function
 * 		2. Integrate into main with state machine for start and stop, logging, and reset.
 * 		3. Integrate timer0 interrupt.
 * 		4. OPTIONAL: implement logging onto sdcard.
 */

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
