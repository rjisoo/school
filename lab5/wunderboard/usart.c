/**
 * TODO:
 *
 * 	1. Write Receiver function
 * 	2. Write Receiver interrupt function
 * 	3. OPTIONAL: make txbuffer dynamic, as well as the rx buffer dynamic.
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "usart.h"

//#define F_CPU 1000000U
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)
#define MAX_BUFF 256


volatile uint8_t TxBuff[MAX_BUFF]; // this is a wrap-around buffer
volatile uint8_t TxNextByte; // position of next byte to be sent
volatile uint8_t TxFree; // position of next free byte of buffer
volatile uint8_t USARTSending; // 1 = sending is in progress

#if DEBUG == 1

/** This function needs to setup the variables used by the UART to enable the UART and tramsmit at 9600bps.
 *  This function should always return 0. Remember, by defualt the Wunderboard runs at 1mHz for its
 *  system clock. By default, this disables transmitter.
 */
uint8_t initializeUSART1(void) {

	/* Set baud rate */
	// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR1H = (BAUD_PRESCALE >> 8);
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRR1L = BAUD_PRESCALE;

	/* Set the U2X1 bit */
	UCSR1A = (1 << U2X1);

	/* Disable transmitter and receiver and their interrupts*/
	UCSR1B |= (1<<TXEN1)|(1<<TXCIE1); //enable transmitter and transmitter complete interrupt
	UCSR1B |= (1<<RXEN1)|(1<<RXCIE1); //enable receiver and receive complete interrupt

	/* Set frame format: 8data, 1stop bit */
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
	UCSR1C &= ~(1 << USBS1);

	/* Initialize Tx buffer variables */
	TxBuff[0] = '\0'; // clear the first byte of buffer
	TxNextByte = 0; // set "next byte to send" to beginning
	TxFree = 0; // next free byte is also beginning of buffer
	USARTSending = 0; // clear "sending in progress" flag

	return 0;
}

uint8_t SendByteUSART1(uint8_t data, FILE *stream){

	register int ReturnStatus = 0; // return 0 for success
	register int TxFree_last; // space to save last TxFree

	if (USARTSending == 0) {
		USARTSending = 1; // set "sending in progress" flag
		UDR1 = data; // send the first byte!
	} else {
		UCSR1B &= ~(1 << TXCIE1); // disable the Tx Complete interrupt
		TxBuff[TxFree] = data;
		// increment the next free byte index, while saving last value
		TxFree_last = TxFree++;

		// check for wrap-around
		if (TxFree == MAX_BUFF) {// if we reached the end of the buffer -
			TxFree = 0; // start back at the beginning
		}
		if (TxFree == TxNextByte){ // if buffer is full -
			// bump back the index so transmit routine doesn't think buffer's empty
			TxFree = TxFree_last;
			// return with error code
			ReturnStatus = EOF;
		}
		UCSR1B |= (1 << TXCIE1); // enable the Tx Complete interrupt
	}
	return ReturnStatus; // return with status code
}

#endif // DEBUG
ISR(USART1_TX_vect){
	if (TxNextByte == TxFree){  // if nothing to send -
		USARTSending = 0;   // clear "sending in progress" flag
		return; // then we have nothing to do, so return
	   }

	   // set "sending in progress" flag
	   USARTSending = 1;

	   // send the next byte on UART0 port
	   UDR1 = TxBuff[TxNextByte];

	   // increment index and check for wrap-around
	   TxNextByte++;
	   if (TxNextByte == MAX_BUFF){ // if we reached the end of the buffer -
		   TxNextByte = 0; // then start back at the beginning
	   }
}
