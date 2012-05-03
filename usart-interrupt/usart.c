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
	UCSR1B |= (1<<RXEN1)|(1<<RXCIE1);

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

	if (UartSendingInProgress == 0) {
		UartSendingInProgress = 1; // set "sending in progress" flag
		UDR1 = data; // send the first byte!
	} else {
		UCSR1B &= ~(1 << TXCIE1); // disable the Tx Complete interrupt
		TxBuff[UartBufferNextFree] = data;
		// increment the next free byte index, while saving last value
		UartBufferNextFree_last = UartBufferNextFree++;

		// check for wrap-around
		if (UartBufferNextFree == MAX_BUFF) {// if we reached the end of the buffer -
			UartBufferNextFree = 0; // start back at the beginning
		}
		if (UartBufferNextFree == UartBufferNextByteToSend){ // if buffer is full -
			// bump back the index so transmit routine doesn't think buffer's empty
			UartBufferNextFree = UartBufferNextFree_last;
			// return with error code
			ReturnStatus = EOF;
		}
		UCSR1B |= (1 << TXCIE1); // enable the Tx Complete interrupt
	}
	return ReturnStatus; // return with status code
}

uint8_t GetByteUSART1(FILE *stream){
	return UDR1;
}
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
