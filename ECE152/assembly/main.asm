.NOLIST
.INCLUDE	"usb647def.inc"
.LIST

.DEF		A = R16
.DEF 	USART = R17
.DEF		I = R21
.DEF 	J = R22
.EQU 	LF = 10
.EQU 	FCPU = 1000000

.CSEG
.ORG 	0x0000
START:
	; Setup stack
	LDI		A, LOW(RAMEND)
	OUT		SPL, A
	LDI		A, HIGH(RAMEND)
	OUT		SPH, A

	; Main function
	RCALL	INITIALIZE
	RCALL	USART_INIT
	RCALL	CLEAR_ARRAY
	LDI		I, 0b10000000
	OUT		PORTB, I	; Set LED Color
	RCALL 	USART_STRING_TX
	.db "This text is being ent over USART!",LF,0
	
	
MAIN:
	RCALL 	USART_BYTE_RX
	RCALL 	USART_BYTE_TX
	RCALL 	LED_PINA
	
	
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

USART_BYTE_RX:
	LDS 		I, UCSR1A
	SBRS 	I, RXC1
	rjmp 	USART_BYTE_RX
	LDS 		USART, UDR1
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
	
LED_PINA:
	IN 		I, PINA
	OUT 		PORTC, I
	RET
	