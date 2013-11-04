#ifndef USART_H
#define USART_H

#define DEBUG 1

#if DEBUG == 1
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "ringbuff.h"

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

RingBuff_t Tx;
volatile uint8_t primed;

uint8_t initializeUSART1(void) {

	/* Set baud rate */
	// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR1H = (BAUD_PRESCALE >> 8);
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRR1L = BAUD_PRESCALE;

	/* Set the U2X1 bit */
	UCSR1A = (1 << U2X1);

	/* Enable transmitter */
	UCSR1B |= (1 << TXEN1); //| (1 << RXEN1);

	/* Enable Transmitter and Transmitter Complete Interrupt */
	UCSR1B |= (1<<TXEN1)|(1<<TXCIE1);

	/* enable Receiver and Receiver Complete Interrupt */
	UCSR1B |= (1<<RXEN1)|(1<<RXCIE1);

	/* Set frame format: 8data, 1stop bit */
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
	UCSR1C &= ~(1 << USBS1);

	RingBuffer_InitBuffer(&Tx);
	primed = 0;

	return 0;
}

/** This function needs to write a single byte to the UART. It must check that the UART is ready for a new byte
 and return a 1 if the byte was not sent.
 @param [in] data This is the data byte to be sent.
 @return The function returns a 1 or error and 0 on successful completion.*/
uint8_t SendByteUSART1(uint8_t data, FILE *stream) {

	if (primed == 0){
		UDR1 = data;
		primed = 1;
		return 0;
	} else if (primed == 1){
		while (RingBuffer_IsFull(&Tx)); //block until ring buffer isn't full.
		RingBuffer_Insert(&Tx, data);
		return 0;
	} else {
		return EOF;
	}
}

/*uint8_t GetByteUSART1(FILE *stream){
	while (!(UCSR1A & (1<<RXC1)));
	return UDR1;
}*/

//FILE usart_io = FDEV_SETUP_STREAM(SendByteUSART1, GetByteUSART1, _FDEV_SETUP_RW);
FILE usart_out = FDEV_SETUP_STREAM(SendByteUSART1, NULL, _FDEV_SETUP_WRITE);
#endif
#endif
