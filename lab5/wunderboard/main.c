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
#include "timer.h"

volatile uint8_t count;
volatile uint8_t direction; //1 == up, 0 == down

int main (void){
	initWunderboard();
	initializeUSART1();
	initializeTIMER0();
	count = 0;
	direction = 1;
	sei();
	setTIMER0(5, 255);


	return 0;
}

ISR (TIMER0_COMPA_vect) {
	//if direction up & count == 50
	//switch direction begin counting down.
	//otherwise count up.

	//if direction down & count == 0
	//switch direction begin counting up
	//otherwise count down
}

ISR (BADISR_vect){ // Catch bad interrupts not defined.
	setArrayRed(~PORTC);
}
