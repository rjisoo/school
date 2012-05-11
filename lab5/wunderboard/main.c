/**
 * TODO:
 * 		1. Make itoa function
 * 		2. Make receive usart work with strings.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "usart.h"
#include "wunderboard.h"

int main (void){



	return 0;
}

ISR (USART1_RX_vect){
	//uint8_t received = UDR1;
	setArrayGreen(~PORTC);

}

ISR (BADISR_vect){
	setArrayRed(~PORTC);
}
