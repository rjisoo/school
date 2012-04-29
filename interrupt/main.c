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

/** Setup for Interrupt Mode */
#include <avr/interrupt.h>

/** global Variables */
#define F_CPU 1000000U

uint8_t count;
//enum states {init, idle, start, stop} state;

/** Main Program */
int main(void) {

	/** Local Variables */

	/** Initialize and Setup */
	//state = init;
	count = 0;
	initialize();
	clearArray();
	//setArrayAmber(0b11110000);
	PORTB = 0b110000000;
	PORTC = 0;

	//clearArray();
	//initializeUART();
	initializeTIMER0();
	//setTIMER0(5, 255);

	/** Enable Interrupts */
	sei();

	setTIMER0(5, 255);
	/** Main function */
	while (1){

	}
	return 0;
}

/** ISR Functions */

//TIMER0 Elapsed
ISR (TIMER0_COMPA_vect){
	//code
	//setArrayAmber(~PORTC);
	PORTC = ~PORTC;
	count++;
}

/*ISR(USART1_RX_vect){
   // Code to be executed when the USART receives a byte here
	uint8_t received;
	received = UDR1;
	if (received == 's'){
		if (state == idle){
			state = start;
			setTIMER0(5, 255);
		} else if (state == start){
			stopTIMER0();
			state = stop;
		}
	}
}*/

//Catch unexpected interrupt
ISR(BADISR_vect) {
	// user code here
	//while (SendStringUART("ERROR!\r\n") == 1);
	PORTE = 0;
	setArrayRed(~PORTC);
}
