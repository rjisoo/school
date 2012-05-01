#ifndef USART_H
#define USART_H

#define DEBUG 1

#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF 0
#endif

#if DEBUG == 1
uint8_t initializeUSART(void);
uint8_t SendStringUSART(uint8_t *data);
#endif
#endif
