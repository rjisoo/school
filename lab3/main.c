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
#include <stdlib.h>
#include <string.h>
#include "ff.h"
#include "diskio.h"

/** Constants */
#define F_CPU 1000000UL
#define DEBUG 0

/// Success error code
#define ERR_NONE 0x00

/// Failed to mount SDC/MMC error code
#define ERR_FMOUNT 0x01

/// No SDC/MMC present error code
#define ERR_NODISK 0x02

/// Unable to initialize FAT file system error code
#define ERR_NOINIT 0x03

/// MMC/SDC write protected error code
#define ERR_PROTECTED 0x04

/** Global Variables */

/** Functions */

/** The clearArray() function turns off all LEDS on the Wunderboard array. It accepts no inputs and returns nothing*/
void clearArray(void) {
	PORTC = 0x00;
	PORTB |= (1 << PB6) | (1 << PB7); /** Enable latches*/
	PORTB &= ~((1 << PB6) | (1 << PB7)); /** Disable latches*/
}

/** The initialize() function initializes all of the Data Direction Registers for the Wunderboard. Before making changes to DDRx registers, ensure that you have read the peripherals section of the Wunderboard user guide.*/
void initialize(void) {
	/** Port A is the switches and buttons. They should always be inputs. ( 0 = Input and 1 = Output )*/
	DDRA = 0b00000000;

	/** Port B has the LED Array color control, SD card, and audio-out on it. Leave DDRB alone. ( 0 = Input and 1 = Output )*/
	DDRB = 0b11000111;

	/** Port C is for the 'row' of the LED array. They should always be outputs. ( 0 = Input and 1 = Output )*/
	DDRC = 0b11111111;

	/** Port D has the Serial on it. Leave DDRB alone. ( 0 = Input and 1 = Output )*/
	DDRD = 0b00000000;

	/** Port E has the LED Array Column control out on it. Leave DDRE alone. ( 0 = Input and 1 = Output )*/
	DDRE = 0b00000111;

	/** Port F has the accelerometer and audio-in on it. Leave DDRF alone. ( 0 = Input and 1 = Output )*/
	DDRF = 0b00000000;
}

/**
 * @brief Initializes the SDC/MMC and mounts the FAT filesystem, if it exists.
 * 
 * Initializes the connected SDC/MMC and mounts the FAT filesystem, if it
 * exists. Returns error code on failure.
 * 
 * @param fs Pointer to FATFS structure
 * @return Returns ERR_FMOUNT, ERR_NODISK, ERR_NOINIT, or ERR_PROTECTED on error, or ERR_NONE on success.
 */
uint8_t initializeFAT(FATFS* fs) {
	DSTATUS driveStatus;

	// Mount and verify disk type
	if (f_mount(0, fs) != FR_OK) {
		// Report error
		return ERR_FMOUNT;
	}

	driveStatus = disk_initialize(0);

	// Verify that disk exists
	if (driveStatus & STA_NODISK) {
		// Report error
		return ERR_NODISK;
	}

	// Verify that disk is initialized
	if (driveStatus & STA_NOINIT) {
		// Report error
		return ERR_NOINIT;
	}

	// Verify that disk is not write protected
	if (driveStatus & STA_PROTECT) {
		// Report error
		return ERR_PROTECTED;
	}

	return ERR_NONE;
}

#if DEBUG == 1
/** This function needs to setup the variables used by the UART to enable the UART and tramsmit at 9600bps. This 
 function should always return 0. Remember, by defualt the Wunderboard runs at 1mHz for its system clock.*/
unsigned char initializeUART(void)
{
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

	return 0;
}

/** This function needs to write a single byte to the UART. It must check that the UART is ready for a new byte 
 and return a 1 if the byte was not sent.
 @param [in] data This is the data byte to be sent.
 @return The function returns a 1 or error and 0 on successful completion.*/
unsigned char sendByteUART(uint8_t data) {

	if (!(UCSR1A & (1<<UDRE1))) {
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
unsigned char sendStringUART(char* str) {
	uint8_t length = strlen((const char *) data);
	uint8_t i;
	if (SendByteUART(data[0]) == 1) {
		return 1;
	} else {
		for (i = 1; i < length; i++) {
			while (SendByteUART(data[i]));
		}
	}
	return 0;
}
#else
#define initializeUART()
#define sendByteUART( data)
#define sendStringUART(str)
#endif // DEBUG
/** This function needs to setup the variables used by TIMER0 Compare Match (CTC) mode with 
 a base clock frequency of clk/1024. This function should return a 1 if it fails and a 0 if it
 does not. Remember, by default the Wunderboard runs at 1mHz for its system clock.
 @return This function returns a 1 is unsuccessful, else return 0.*/
unsigned char initializeTIMER0(void) {
	/* Set the CTC mode */
	TCCR0A |= (2 << WGM00);

	/* Set the Clock Frequency */
	TCCR0B |= (5 << CS00);

	/* Set initial count value */
	OCR0A = 100;

	return 0;
}

/** This function checks if TIMER0 has elapsed. 
 @return This function should return a 1 if the timer has elapsed, else return 0*/
unsigned char checkTIMER0(void) {

	if (TIFR0 & (1 << OCF0A)){
		return 1;
	}
	return 0;
}

/** This function takes two values, clock and count. The value of count should be copied into OCR0A and the value of clock should be used to set CS02:0. The TCNT0 variable should also be reset to 0 so that the new timer rate starts from 0.  
 @param [in] clock Insert Comment
 @param [in] count Insert Comment
 @return The function returns a 1 or error and 0 on successful completion.*/
unsigned char setTIMER0(unsigned char clock, unsigned char count) {

}

/** Main Function */
int main(void) {
	/** Local Varibles */
	FATFS fs;
	FIL log;

	initialize();

	// Initialize TIMER/COUNTER0

	// Initialize file system, check for errors

	// Open file for writing, create the file if it does not exist, truncate existing data, check for errors

	// Set TIMER/COUNTER0 period, check for errors

	// While switch A7 is on
	while (PINA & (1 << PA7)) {
		// If TIMER/COUNTER0 has elapsed
		// Read accelerometer data, write to file, check for errors
	}

	// Close the file and unmount the file system, check for errors
}
