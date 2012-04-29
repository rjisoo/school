/**
 @file main.c
 @brief Lab 3 Starter Code
 @version .01
 @mainpage Lab 3 Starter Code

 @section intro Code Overview
 
 @section hw Hardware Pin Out
 Port A:
 A0 - A3 : Push Buttons
 A4 - A7 : Slide Switches

 Port B:
 B0 - B3 : SPI (SD Card)
 B4		: Nothing
 B5		: Audio Out
 B6 		: Red Enable
 B7 		: Green Enable

 Port C:
 C0 - C7 : LED Array (Row)

 Port D:
 D0 - D1 : Nothing
 D2		: Serial RX
 D3		: Serial TX
 D4 - D7	: Nothing

 Port E:
 E0 - E2 : LED Array (Column)
 E3		: USB (UID)
 E4 - E5	: Nothing
 E6		: Relay
 E7		: Nothing

 Port F:
 F0 		: ADC Channel 0
 F1 		: ADC Channel 1
 F2 		: ADC Channel 2
 F3 		: ADC Channel 3
 F4		: ADC Channel 4 (Audio In)
 F5 		: ADC Channel 5 (Accel X Axis)
 F6 		: ADC Channel 6 (Accel Y Axis)
 F7 		: ADC Channel 7 (Accel Z Axis (if installed))

 */

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include "initialize.h"
#include "uart.h"
#include "timer.h"
enum states {init, idle, start, stop} state;

/** Setup for Interrupt Mode */
#include <avr/interrupt.h>

/** global Variables */
#define F_CPU 1000000U

uint8_t count;

/** Main Program */
int main(void) {

	/** Local Variables */

	/** Initialize and Setup */
	count = 0;
	state = init;
	//initialize();

	//clearArray();
	initializeUART();
	//initializeTIMER0();
	//setTIMER0(5, 255);

	/** Enable Interrupts */
	sei();

	/** Main function */
	while (1){

		switch (state) {

		case init:
			while (SendStringUART("Initializing device...\r\n") == 1);
			initialize();
			clearArray();
			initializeTIMER0();
			while (SendStringUART("Press 's' to start logging.\r\n") == 1);
			while (SendStringUART("Going into idle...\r\n") == 1);
			break;

		case idle:
			break;

		case start:
			break;

		case stop:
			while (SendStringUART("Shutting down...\r\n") == 1);
			stopTIMER0();
			break;
		}

	}
	
	return 0;
}

/** ISR Functions */

//TIMER0 Elapsed
ISR (TIMER0_COMPA_vect){
	//code
	uint8_t i;
	count ++;
	if (count > 1){
		count = 0;
		while (SendStringUART("Timer elapsed!\r\n") == 1);
		setArrayGreen(0xff);
	} else {
		clearArray();
	}
}

ISR(UART_RXC_vect)
{
   // Code to be executed when the USART receives a byte here
	if (UDR1 == 's'){
		if (state == idle){
			state = start;
			setTIMER0(5, 255);
		} else if (state == start){
			state = stop;
		}
	}
}

//Catch unexpected interrupt
ISR(BADISR_vect) {
	// user code here
	while (SendStringUART("ERROR!\r\n") == 1);
	PORTE = 0;
	setArrayRed(~PORTC);
}
