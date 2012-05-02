#ifndef USART_H
#define USART_H

#include <stdio.h>
#define DEBUG 1

#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF 0
#endif

#if DEBUG == 1
uint8_t initializeUSART1(void);
uint8_t SendByteUSART1(uint8_t data, FILE *stream);
#endif
#endif
