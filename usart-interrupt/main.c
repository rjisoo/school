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
#include <stdio.h>
#include "usart.h"
#include "wunderboard.h"


int main (void){
	//uint8_t string[] = "This is a test string\r\n";
	FILE uart_output = FDEV_SETUP_STREAM(SendByteUSART1, NULL, _FDEV_SETUP_WRITE);
	stdout = &uart_output;

	initWunderboard();
	clearArray();
	initializeUSART1();
	sei();

	while (1){
	printf("This is a test string\r\n");
	setArrayGreen(~PORTC);
	_delay_ms(500);
	}
	return 0;
}
