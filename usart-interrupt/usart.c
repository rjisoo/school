#include <avr/io.h>
#include <string.h>
#include "usart.h"

#define F_CPU 1000000U
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

#if DEBUG == 1
/** This function needs to setup the variables used by the UART to enable the UART and tramsmit at 9600bps. This
 function should always return 0. Remember, by defualt the Wunderboard runs at 1mHz for its system clock.
 By default, this enables transmitter and receiver. */
uint8_t initializeUSART(void) {

	/* Set baud rate */
	// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR1H = (BAUD_PRESCALE >> 8);
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRR1L = BAUD_PRESCALE;

	/* Set the U2X1 bit */
	UCSR1A = (1 << U2X1);

	/* Enable transmitter */
	UCSR1B |= (1 << TXEN1) | (1 << RXEN1);

	/* Set frame format: 8data, 1stop bit */
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
	UCSR1C &= ~(1 << USBS1);

	//UCSR1B |= (1 << RXCIE1); // Enable the USART Receive Complete interrupt (USART_RXC)

	return 0;
}

/** This function needs to write a single byte to the UART. It must check that the UART is ready for a new byte
 and return a 1 if the byte was not sent.
 @param [in] data This is the data byte to be sent.
 @return The function returns a 1 or error and 0 on successful completion.*/
uint8_t SendByteUSART(uint8_t data) {

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
uint8_t SendStringUSART(uint8_t *data) {

	uint8_t length = strlen((const char *) data);
	uint8_t i;
	if (SendByteUSART(data[0]) == 1) {
		return 1;
	} else {
		for (i = 1; i < length; i++) {
			while (SendByteUSART(data[i]));
		}
	}
	return 0;
}

uint8_t checkReceiveByteUSART(void) {
	return ((UCSR1A & (1 << RXC1)));
}

uint8_t ReceiveByteUSART(void) {
	while (!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

/*
 * Enables or disables the USART Transmitter.
 * Parameters: position has to be either a 1 or zero
 * Function: If position == ON, enable USART transmitter. if position == OFF
 * 			 disable USART Transmitter.
 * Returns: 0 on completion or 1 on error.
 */
uint8_t EnableTxUSART(uint8_t position) {
	return 0;
}

/*
 * Enables or disables the USART Receiver.
 * Parameters: position has to be either a 1 or zero
 * Function: If position == ON, enable USART Receiver. if position == OFF
 * 			 disable USART Receiver.
 * Returns: 0 on completion or 1 on error.
 */
uint8_t EnableRxUSART(uint8_t position) {
	return 0;
}

/*
 * Enables or disables the USART Transmit Compete Interrupt.
 * Parameters: position has to be either a 1 or zero
 * Function: If position == ON, enable USART transmit complete interrupt. if position == OFF
 * 			 disable USART Transmit complete interrupt.
 * Returns: 0 on completion or 1 on error.
 */
uint8_t EnableTxInterUSART(uint8_t position) {
	return 0;
}

/*
 * Enables or disables the USART Receive Compete Interrupt.
 * Parameters: position has to be either a 1 or zero
 * Function: If position == ON, enable USART receive complete interrupt. if position == OFF
 * 			 disable USART receive complete interrupt.
 * Returns: 0 on completion or 1 on error.
 */
uint8_t EnableRxInterUSART(uint8_t position) {
	return 0;
}

/*
 * Configures USART to be used in interrupt mode
 * Parameters: position has to be a 1 or zero
 * Function: if position == ON, enable interrupt mode. if position == OFF, disable interrupt mode.
 * Returns: 0 on completion, 1 on error.
 */
uint8_t EnableInterUSART(uint8_t position) {
	return 0;
}
#endif // DEBUG
