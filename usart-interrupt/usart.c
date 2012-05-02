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
#include <stdbool.h>
#include "usart.h"

#define F_CPU 1000000U
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)
#define MAX_BUFF 256

volatile uint8_t TxBuff[MAX_BUFF]; // this is a wrap-around buffer
volatile uint8_t UartBufferNextByteToSend; // position of next byte to be sent
volatile uint8_t UartBufferNextFree; // position of next free byte of buffer
volatile uint8_t UartSendingInProgress; // 1 = sending is in progress

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
	//UCSR1B &= ~((1<<TXEN1) | (1<<RXEN1) | (1<<TXCIE1) | (1<<RXCIE1) | (1<<UDRIE1));
	UCSR1B |= (1<<TXEN1)|(1<<TXCIE1); //enable transmitter and transmitter complete interrupt

	/* Set frame format: 8data, 1stop bit */
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
	UCSR1C &= ~(1 << USBS1);

	TxBuff[0] = '\0'; // clear the first byte of buffer
	UartBufferNextByteToSend = 0; // set "next byte to send" to beginning
	UartBufferNextFree = 0; // next free byte is also beginning of buffer
	UartSendingInProgress = 0; // clear "sending in progress" flag

	return 0;
}

uint8_t SendByteUSART1(uint8_t data, FILE *stream){
	register int ReturnStatus = 0; // return 0 for success
	register int UartBufferNextFree_last; // space to save last UartBufferNextFree
	/*if (data == '\n') {
	 SendByteUSART('\r', stream);
	 }*/
	//while (!(UCSR1A & (1 << UDRE1)));
	//UDR1 = data;
	//return 0;
	// if no send is already in progress, then "prime the pump" by sending directly to UART
	if (UartSendingInProgress == 0) {
		// set "sending in progress" flag
		UartSendingInProgress = 1;
		// send the first byte!
		UDR1 = data;
	} else {
		// disable the Tx Complete interrupt
		UCSR1B &= ~(1 << TXCIE1);

		TxBuff[UartBufferNextFree] = data;

		// increment the next free byte index, while saving last value
		UartBufferNextFree_last = UartBufferNextFree++;

		// check for wrap-around
		if (UartBufferNextFree == MAX_BUFF) // if we reached the end of the buffer -
			UartBufferNextFree = 0; // start back at the beginning

		if (UartBufferNextFree == UartBufferNextByteToSend){ // if buffer is full -
			// bump back the index so transmit routine doesn't think buffer's empty
			UartBufferNextFree = UartBufferNextFree_last;
			// return with error code
			ReturnStatus = EOF;
		}
		// enable the Tx Complete interrupt
		UCSR1B |= (1 << TXCIE1);
	}

	// return with status code
	return ReturnStatus;
}

/**
 * This function will send a string through the USART. It enables the transmitter and its interrupt,
 * waits for UDR1 to be ready, and then transmits. It returns 0 if the string was sent, and
 * returns 1 if the string was not sent or the string was too big.
 */
#endif // DEBUG
ISR(USART1_TX_vect){
	if (UartBufferNextByteToSend == UartBufferNextFree){  // if nothing to send -
		UartSendingInProgress = 0;   // clear "sending in progress" flag
		return; // then we have nothing to do, so return
	   }

	   // set "sending in progress" flag
	   UartSendingInProgress = 1;

	   // send the next byte on UART0 port
	   UDR1 = TxBuff[UartBufferNextByteToSend];

	   // increment index and check for wrap-around
	   UartBufferNextByteToSend++;
	   if (UartBufferNextByteToSend == MAX_BUFF){ // if we reached the end of the buffer -
		   UartBufferNextByteToSend = 0; // then start back at the beginning
	   }
}
