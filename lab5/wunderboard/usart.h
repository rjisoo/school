#ifndef USART_H
#define USART_H

#include <stdio.h>
#define DEBUG 1

#if DEBUG == 1
uint8_t initializeUSART1(void);
uint8_t SendByteUSART1(uint8_t data, FILE *stream);
uint8_t GetByteUSART1(FILE *stream);
#endif

FILE usart_out = FDEV_SETUP_STREAM(SendByteUSART1, NULL, _FDEV_SETUP_WRITE);
FILE usart_in = FDEV_SETUP_STREAM(NULL, GetByteUSART1, _FDEV_SETUP_READ);

#endif
