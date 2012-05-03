#ifndef USART_H
#define USART_H

#include <stdio.h>
#define DEBUG 1

#if DEBUG == 1
uint8_t initializeUSART1(void);
uint8_t SendByteUSART1(uint8_t data, FILE *stream);
uint8_t GetByteUSART1(FILE *stream);
#endif

#endif
