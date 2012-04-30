#ifndef USART_H
#define USART_H

#define DEBUG 1
#define ON 1
#define OFF 0

#if DEBUG == 1
uint8_t initializeUSART(void);

uint8_t SendByteUSART(uint8_t data);

uint8_t SendStringUSART(uint8_t *data);

uint8_t checkReceiveByteUSART(void);

uint8_t ReceiveByteUSART(void);

uint8_t EnableTxUSART(uint8_t position);

uint8_t EnableRxUSART(uint8_t position);

uint8_t EnableTxInterUSART(uint8_t position);

uint8_t EnableRxInterUSART(uint8_t position);

uint8_t EnableInterUSART(uint8_t position);

#endif
#endif
