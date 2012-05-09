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

volatile enum states {init, idle, start, shutdown, stop} state;
volatile uint8_t count;

int main (void){



	return 0;
}

ISR (USART1_RX_vect){
	uint8_t received = UDR1;
	if (received == 's'){
		if (state == idle){
			state = start;
			printf("Press 's' to stop timer.\n");
			setTIMER0(5, 255);
		} else if (state == start){
			stopTIMER0();
			state = shutdown;
		}
	}
}

ISR (BADISR_vect){
	setArrayRed(~PORTC);
}
