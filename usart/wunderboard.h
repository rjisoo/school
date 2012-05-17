#ifndef WUNDERBOARD_H
#define WUNDERBOARD_H

#include <avr/io.h>
#include <util/delay.h>

/**
 Hardware Pin Out
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
/** The clearArray() function turns off all LEDS on the Wunderboard array.
 *  It accepts no inputs and returns nothing*/
uint8_t clearArray(void) {
	PORTC = 0x00;
	PORTB |= (1 << PB6) | (1 << PB7); /** Enable latches*/
	PORTB &= ~((1 << PB6) | (1 << PB7)); /** Disable latches*/
	return 0;
}

/** Sets the array to Amber and displays the number of rows indicated by rows variable*/
uint8_t setArrayAmber(uint8_t rows) {
	clearArray();
	PORTC = rows;
	PORTB |= (1 << PB6) | (1 << PB7);
	PORTB &= ~(1 << PB6) | (1 << PB7);
	return 0;
}

uint8_t setArrayGreen(uint8_t rows) {
	clearArray();
	PORTC = rows;
	PORTB |= (1 << PB7);
	PORTB &= ~(1 << PB7);
	return 0;
}

uint8_t setArrayRed(uint8_t rows) {
	clearArray();
	PORTC = rows;
	PORTB |= (1 << PB6);
	PORTB &= ~(1 << PB6);
	return 0;
}

/** The initialize() function initializes all of the Data Direction Registers for the Wunderboard.
    Before making changes to DDRx registers, ensure that you have read the peripherals section of
    the Wunderboard user guide.
*/
uint8_t initWunderboard(void) {
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

	clearArray();

	return 0;
}

#endif
