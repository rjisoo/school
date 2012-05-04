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
#include "timer.h"
#include "adc.h"

uint8_t read;
FILE uart_io = FDEV_SETUP_STREAM(SendByteUSART1, NULL, _FDEV_SETUP_WRITE);
volatile enum states {init, idle, start, shutdown, stop} state;
volatile uint8_t count;

int main (void){
	/* Directs serial communication to stdout for usual print and functions */
	stdout = &uart_io;
	state = init;

	while (1){
		switch (state){

		case init:
			/*
			 * Setup wunderboard, initialize USART, start global interrupts.
			 * Also, print directions.
			 */
			initWunderboard();
			clearArray();
			initializeUSART1();
			initializeTIMER0();
			sei();
			count = 0;
			printf("Press 's' to start.\n");
			state = idle;
			break;

		case idle:
			/*
			 * Wait for input from USART to match 's'.
			 */
			break;

		case start:
			break;

		case shutdown:
			printf("Shutting down...\n");
			_delay_ms(50);
			state = stop;
			break;

		case stop:
			setArrayGreen(0xff);
			break;
		}
	}
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

ISR (TIMER0_COMPA_vect) {
	count++;
	if (count > 1) {
		printf("ADC Value: %d.\n", read_adc(PF5));
		setArrayAmber(0b00111100);
		count = 0;
	} else {
		clearArray();
	}
}
