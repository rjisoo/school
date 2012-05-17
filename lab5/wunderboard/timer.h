#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

/** This function needs to setup the variables used by TIMER0 Compare Match (CTC) mode with
 a base clock frequency of clk/1024. This function should return a 1 if it fails and a 0 if it
 does not. Remember, by default the Wunderboard runs at 1mHz for its system clock.
 @return This function returns a 1 is unsuccessful, else return 0.*/
uint8_t initializeTIMER0(void) {
	/* Set the CTC mode */
	TCCR0A = (2 << WGM00);

	/* Set the Clock Frequency */
	TCCR0B = (5 << CS20);

	/* Set initial count value */
	OCR0A = 0;

	return 0;
}

/** This function checks if TIMER0 has elapsed.
 @return This function should return a 1 if the timer has elapsed, else return 0*/
uint8_t checkTIMER0(void) {

	if (TIFR0 & (1 << OCF0A)) {
		TIFR0 |= (1 << OCF0A);
		return 1;
	}
	return 0;

}

/** This function takes two values, clock and count. The value of count should be copied into OCR0A
 *  and the value of clock should be used to set CS02:0. The TCNT0 variable should also be reset to 0
 *  so that the new timer rate starts from 0.
 @param [in] clock Insert Comment
 @param [in] count Insert Comment
 @return The function returns a 1 or error and 0 on successful completion.*/
uint8_t setTIMER0(uint8_t clock, uint8_t count) {

	if (clock < 1 || clock > 5) { //makes sure there is a clock and uses the built in clock.
		return 1;
	}

	OCR0A = count;

	TCCR0B &= ~(7 << CS20);
	TCCR0B |= (clock << CS00);

	TIMSK0 = 0; //clear TIMSK0
	TIMSK0 |= (1 << OCIE0A); //enable timer interrupts
	//TIMSK0 = 0b00000010; //enable timer interrupt

	TCNT0 = 0;

	return 0;
}

uint8_t stopTIMER0(void){
	//TIMSK0 &= (0 << OCIE0A); 	//disable timer interrupt
	TIMSK0 &= (0 << OCIE0A);	//Disable timer interrupt

	return 0;
}

#endif
