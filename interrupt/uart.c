#include <avr/io.h>
#include <string.h>
#include "uart.h"


//#define DEBUG 1

#if DEBUG == 1
/** This function needs to setup the variables used by the UART to enable the UART and tramsmit at 9600bps. This
 function should always return 0. Remember, by defualt the Wunderboard runs at 1mHz for its system clock.*/
uint8_t initializeUART(void) {
	/* Set baud rate */
	UBRR1H = 0;
	UBRR1L = 12;

	/* Set the U2X1 bit */
	UCSR1A = (1 << U2X1);

	/* Enable transmitter */
	UCSR1B |= (1 << TXEN1) | (1 << RXEN1);

	/* Set frame format: 8data, 1stop bit */
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
	UCSR1C &= ~(1 << USBS1);

	UCSR1B |= (1 << RXCIE1); // Enable the USART Recieve Complete interrupt (USART_RXC)

	return 0;
}

/** This function needs to write a single byte to the UART. It must check that the UART is ready for a new byte
 and return a 1 if the byte was not sent.
 @param [in] data This is the data byte to be sent.
 @return The function returns a 1 or error and 0 on successful completion.*/
uint8_t SendByteUART(uint8_t data) {

	if (!(UCSR1A & (1 << UDRE1))) {
		return 1;
	} else {
		UDR1 = data;
	}
	return 0;
}

/** This function needs to writes a string to the UART. It must check that the UART is ready for a new byte and
 return a 1 if the string was not sent.
 @param [in] str This is a pointer to the data to be sent.
 @return The function returns a 1 or error and 0 on successful completion.*/
uint8_t SendStringUART(uint8_t *data) {

	uint8_t length = strlen((const char *) data);
	uint8_t i;
	if (SendByteUART(data[0]) == 1) {
		return 1;
	} else {
		for (i = 1; i < length; i++) {
			while (SendByteUART(data[i]))
				;
		}
	}
	return 0;
}

uint8_t checkReceiveByteUART(void){
	return ((UCSR1A & (1 << RXC1)));
}

uint8_t ReceiveByteUART(void) {
	while (!(UCSR1A & (1 << RXC1)));
	return UDR1;
}
#endif // DEBUG
