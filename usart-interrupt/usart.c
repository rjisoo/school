#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "usart.h"

#define F_CPU 1000000U
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

#if DEBUG == 1

#define MAX_BUFF 255
volatile uint8_t txbuf[MAX_BUFF];
volatile uint8_t tlen;
volatile uint8_t tpos;

/** This function needs to setup the variables used by the UART to enable the UART and tramsmit at 9600bps.
 *  This function should always return 0. Remember, by defualt the Wunderboard runs at 1mHz for its
 *  system clock. By default, this disables transmitter.
 */
uint8_t initializeUSART(void) {

	/* Set baud rate */
	// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR1H = (BAUD_PRESCALE >> 8);
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRR1L = BAUD_PRESCALE;

	/* Set the U2X1 bit */
	UCSR1A = (1 << U2X1);

	/* Disable transmitter and receiver */
	UCSR1B &= ~((1 << TXEN1) | (1 << RXEN1));

	/* Set frame format: 8data, 1stop bit */
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
	UCSR1C &= ~(1 << USBS1);

	return 0;
}

/** This function needs to writes a string to the UART. It must check that the UART is ready for a new byte and
 return a 1 if the string was not sent.
 @param [in] str This is a pointer to the data to be sent.
 @return The function returns a 1 or error and 0 on successful completion.*/
uint8_t SendStringUSART(uint8_t *data) {

	uint8_t i;
	tlen = strlen(data);
	tpos = 0;
	for (i = 0; i < tlen; i++){ //put data into transmit buffer
		txbuf[i] = data[i];
	}
	UCSR1B |= (1<<TXEN1)|(1<<UDRIE1); //enalbe transmitter and transmitter interrupt

	while(!(UCSR1A & (1<<UDRE1))); //wait until buffer ready
	UDR1 = 0; //prime buffer

	return 0;
}
#endif // DEBUG

ISR(USART1_UDRE_vect){
	if (tpos < tlen){
		UDR1 = txbuf[tpos]; //send tx buffer through usart
		tpos++;
	} else {
		UCSR1B &= ~((1<<TXEN1)|(1<<UDRIE1)); //otherwise disable transmitter
	}
}
