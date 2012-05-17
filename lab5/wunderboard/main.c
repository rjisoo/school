#include "usart.h"
#include "wunderboard.h"
#include "timer.h"

#define UP 0
#define DOWN 1

volatile enum states {init, idle, count_down, count_up, out, stop} state;
volatile uint8_t count, direction;

/*
 * For direction, 0 means up, 1 means down.
 */
int main(void){
	stdout = stdin = &usart_io;
	initializeUSART1();
	state = init;
	uint8_t display[4];
	sei();

	while (1) {

		switch (state) {
		case init:
				initWunderboard();
				initializeTIMER0();
				count = direction = 0;
				state = out;
				printf("Starting timed counting program!\n");
				setTIMER0(5, 255);
				break;

		case idle:
				break;

		case count_down:
				count--;
				if (count == 0){
					direction = UP;
				}
				state = out;
				break;

		case count_up:
				count++;
				if (count == 50){
					direction = DOWN;
				}
				state = out;
				break;

		case out:
			itoaw(display, count);
			printf("%s\n", display);
			state = idle;
			break;

		case stop:
				printf("Stopping...\n");
				stopTIMER0();
				state = idle;
				break;
		default:
				setArrayAmber(~PORTC);
				break;

		}

	}

	return 0;
}

ISR(USART1_TX_vect){
	if (RingBuffer_IsEmpty(&Tx)){
		primed = 0;
		return;
	} else {
		UDR1 = RingBuffer_Remove(&Tx);
	}
}

ISR (TIMER0_COMPA_vect) {
	if (direction == UP){
		state = count_up;
	} else {
		state = count_down;
	}
	setArrayAmber(~PORTC);
}

ISR (BADISR_vect){ // Catch bad interrupts not defined.
	setArrayRed(~PORTC);
}
