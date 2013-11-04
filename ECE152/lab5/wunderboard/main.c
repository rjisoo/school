#include "usart.h"
#include "wunderboard.h"
#include "timer.h"

#define UP 0
#define DOWN 1

volatile enum states {init, idle, counting, printing, stop50, stop0} state;
volatile uint8_t count, direction;

/*
 * For direction, 0 means up, 1 means down.
 */
int main(void){
	stdout = &usart_out;
	initializeUSART1();
	state = init;
	uint8_t display[4];
	sei();

	while (1) {

		switch (state) {
		case init:
				initWunderboard();
				initializeTIMER0();
				count = 0;
				direction = UP;
				printf("Starting timed counting program!\n");
				setTIMER0(5, 255);
				state = idle;
				break;

		case idle:
				break;

		case counting:
				if (direction == DOWN){
					count --;
				}
				if (direction == UP){
					count ++;
				}
				state = printing;
				break;

		case printing:
				itoaw(display, count);
				printf("%s\n", display);
				if (count == 50){
					state = stop50;
					stopTIMER0();
				} else if (count == 0){
					state = stop0;
					stopTIMER0();
				} else {
					state = idle;
				}
				break;

		case stop50:
				break;

		case stop0:
				break;
		default:
				setArrayRed(~PORTC);
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
	state = counting;
	setArrayAmber(~PORTC);
}

ISR (USART1_RX_vect){
	uint8_t received;
	received = UDR1;
	if (received == 's'){
		if (state == stop50){
			direction = DOWN;
			setTIMER0(5, 255);
		}

		if (state == stop0){
			direction = UP;
			setTIMER0(5, 255);
		}
	}
}

ISR (BADISR_vect){ // Catch bad interrupts not defined.
	setArrayRed(~PORTC);
}
