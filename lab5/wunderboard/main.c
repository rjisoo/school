/**
 * TODO:
 * 		1. Make itoa function
 * 		2. Make receive usart work with strings.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart.h"
#include "wunderboard.h"



int main (void){
	initWunderboard();
	initializeUSART1();
	sei();


	return 0;
}

ISR (BADISR_vect){ // Catch bad interrupts not defined.
	setArrayRed(~PORTC);
}
