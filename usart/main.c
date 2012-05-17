#include "wunderboard.h"
#include "usart.h"
#include "usart_int_tx.h"
#include "ringbuff.h"
#include <string.h>

int main(void){

	stdout = stdin = &usart_io;
	uint8_t in[15];

	initWunderboard();
	initializeUSART1();
	sei();

	while (1){
		printf("Please enter a String:\n");
		scanf("%s", &in);
		printf("You typed: %s\n", in);
	}

	return 0;
}

ISR(USART1_TX_vect){
	if (RingBuffer_IsEmpty(&Tx)){
		primed = 0;
		return;
	} else {
		UDR1 = RingBuffer_Remove(&Tx);
		setArrayGreen(~PORTC);
	}
}

/*ISR(USART1_RX_vect){
	uint8_t read = UDR1;
	RingBuffer_Insert(&Rx, read);
	//reading = 1;
}*/

ISR (BADISR_vect){ // Catch bad interrupts not defined.
	setArrayRed(~PORTC);
}
