/**
 * TODO:
 * 		1. Make itoa function
 * 		2. Make receive usart work with strings.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "usart.h"
#include "wunderboard.h"



int main (void){
	initializeUSART1();
	 stdout = &usart_out;
	 stdin  = &usart_in;
	 sei();


	return 0;
}

ISR (BADISR_vect){ // Catch bad interrupts not defined.
	setArrayRed(~PORTC);
}
