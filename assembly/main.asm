.NOLIST
.INCLUDE	"usb647def.inc"
.LIST

.DEF		A = R16
.DEF 	USART = R17
.DEF		I = R21
.EQU 	CR = 13
.EQU 	FCPU = 1000000

.CSEG
.ORG 	0x0000
	RJMP 	START ;reset
	RETI ;int0
	RETI ;int1
	RETI ;int2
	RETI ;int3
	RETI ;int4
	RETI ;int5
	RETI ;int6
	RETI ;int7
	RETI ;pcint0
	RETI ;usb gen
	RETI ;usb endpoint
	RETI ;wdt
	RETI ;t2ca
	RETI ;t2cb
	RETI ;t2ovf
	RETI ;t1cap
	RETI ;t1ca
	RETI ;t1cb
	RETI ;t1cc
	RETI ;t1ovf
	RJMP	TIMER0_INT

START:
	; Setup stack
	LDI		A, LOW(RAMEND)
	OUT		SPL, A
	LDI		A, HIGH(RAMEND)
	OUT		SPH, A

	; Main function
	RCALL	INITIALIZE
	RCALL	CLEAR_ARRAY
	RCALL	USART_INIT
	LDI		A, 0b10000000
	OUT		PORTB, A	; Set LED Color
	RCALL 	TIMER0_INIT
	SEI
	
	MAIN:
	RCALL 	USART_STRING_TX
	.db "This is a longer test string! And I'm adding even more letters..",CR,0
	

	;CLR		A
	

END: RJMP	MAIN
	
INITIALIZE:
	; Setup DDRA
	CLR		A
	OUT		DDRA, A
	
	; Setup DDRD
	OUT		DDRD, A
	
	; Setup DDRF
	OUT		DDRF, A
	
	; Setup DDRB
	LDI		A, 0b11000000
	OUT		DDRB, A
	
	; Setup DDRC
	SER		A
	OUT		DDRC, A
	
	; Setup DDRE
	LDI		A, 0b00000111
	OUT		DDRE, A
	RET

CLEAR_ARRAY:
	; Clear Array
	CLR		A
	OUT		PORTC, A

	; Enable Latches
	LDI		A, ((1 << PB6) | (1 << PB7))
	OUT		PORTB, A

	; Disable Latches
	LDI		A, ~((1 << PB6) | (1 << PB7))
	OUT		PORTB, A
	RET

USART_INIT:
	; Set Baud rate
	CLR		A
	STS		UBRR1H, A
	LDI		A, 12
	STS		UBRR1L, A
	; Set U2X1 Bit
	LDI		A, (1 << U2X1)
	STS		UCSR1A, A
	; Enable Tx and Rx
	;CLR 		A
	LDI		A, ((1 <<TXEN1) | (1 << RXEN1) )
	STS		UCSR1B, A
	; Set frame to 8-bit, 1 stop, no parity
	;LDS		A, UCSR1C
	LDI		A, ((1 << UCSZ10) | (1 << UCSZ11) | (0 << USBS1))
	;CBR 		A, USBS1
	STS 		UCSR1C, A
	RET


USART_BYTE_TX:
	LDS		I, UCSR1A 
	SBRS	I, UDRE1
	rjmp		USART_BYTE_TX
	STS		UDR1, USART
	RET
	
USART_STRING_TX:
	; Get string location from stack
	POP 	ZH
	POP 	ZL
	lsl 		ZL
	rol 		ZH
	string_loop:
	; Load valude from address
	LPM
	; Move to general register
	MOV 	USART, r0
	; Increment location in string
	adiw 	ZL, 1
	; check if null char
	CPI 		USART, 0
	BREQ 	USART_SEND_END
	; Otherwise, Send to USART
	RCALL 	USART_BYTE_TX
	rjmp 	string_loop
	
	USART_SEND_END:
	; fix stack
	lsr 		ZH
	ror 		ZL
	push 	ZL
	push 	ZH
	RET
	
TIMER0_INIT:
	CLR		A
	LDI		A, (2 << WGM00)
	STS		TCCR0A, A
	CLR		A
	LDI		A, (5 << CS02)
	STS		TCCR0B, A
	RET

TIMER0_SET:
	CLR		A
	LDI		A, 255
	STS		OCR0A, A
	LDS		A, TCCR0B
	ANDI	A, ~(7 << CS02)
	ORI		A, (5 << CS02)
	STS		TCCR0B, A
	CLR		A
	STS		TIMSK0, A
	STS		TCNT0, A
	ORI		A, (1 << OCIE0A)
	STS		TIMSK0, A
	RET
	
TIMER0_INT:
	PUSH 	A
	IN 		A, SREG
	PUSH 	A
	IN		A, PINC
	COM		A
	OUT		PORTC, A
	POP 	A
	OUT 	SREG, A
	POP 	A
	RETI
	