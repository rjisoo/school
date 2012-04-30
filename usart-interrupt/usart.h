#ifndef USART_H
#define USART_H

#define DEBUG 1

#if DEBUG == 1
uint8_t initializeUSART(void);

uint8_t SendByteUSART(uint8_t data);

uint8_t SendStringUSART(uint8_t *data);

uint8_t checkReceiveByteUSART(void);

uint8_t ReceiveByteUSART(void);

#endif
#endif
