#include <avr/io.h>
#include "initialize.h"

/** The clearArray() function turns off all LEDS on the Wunderboard array.
 *  It accepts no inputs and returns nothing*/
void clearArray(void) {
	PORTC = 0x00;
	PORTB |= (1 << PB6) | (1 << PB7); /** Enable latches*/
	PORTB &= ~((1 << PB6) | (1 << PB7)); /** Disable latches*/
}

/** Sets the array to Amber and displays the number of rows indicated by rows variable*/
void setArrayAmber(uint8_t rows) {
	clearArray();
	PORTC = rows;
	PORTB |= (1 << PB6) | (1 << PB7);
	PORTB &= ~(1 << PB6) | (1 << PB7);
}

void setArrayGreen(uint8_t rows) {
	clearArray();
	PORTC = rows;
	PORTB |= (1 << PB7);
	PORTB &= ~(1 << PB7);
}

void setArrayRed(uint8_t rows) {
	clearArray();
	PORTC = rows;
	PORTB |= (1 << PB6);
	PORTB &= ~(1 << PB6);
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
