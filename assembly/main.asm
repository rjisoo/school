.INCLUDE	"usb647def.inc"

.DEF	A = R16
.DEF	I = R21
.DEF	J = R22

.ORG	$000

.DSEG
fstring: .db "This is a string",'\n',0

.CSEG
MAIN:
	; Setup stack
	LDI		A, LOW(RAMEND)
	OUT		SPL, A
	LDI		A, HIGH(RAMEND)
	OUT		SPH, A

	; Main function
	RCALL	INITIALIZE
	RCALL	CLEAR_ARRAY
	RCALL	USART_INIT
	LDI		A, 0b11000000
	OUT		PORTB, A	; Set LED Color

	CLR		A

	FOR:
		LDI		XL, LOW(fstring)
		LDI		XH, HIGH(fstring)
		LDI		A, 19
		RCALL	USART_STRING_TX
		RJMP	FOR

END: RJMP	END
	
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
	LDS		A, UCSR1B
	LDI		A, ((1 << TXEN1) | (1 << RXEN1))
	STS		UCSR1B, A
	; Set frame to 8-bit, 1 stop, no parity
	LDS		A, UCSR1C
	LDI		A, ((1 << UCSZ10) | (1 << UCSZ11))
	LDI		A, ~(1 << USBS1)
	RET


USART_BYTE_TX:
	LDS		I, UCSR1A 
	SBRS	I, UDRE1
	rjmp	USART_BYTE_TX
	STS		UDR1, J
	RET

USART_STRING_TX:
	LD		J, X+
	CPI		J, 0
	BREQ	END_STR
	RCALL	USART_BYTE_TX
END_STR:
	RET