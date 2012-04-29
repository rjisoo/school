#ifndef UART_H
#define UART_H

#define DEBUG 1

#if DEBUG == 1
uint8_t initializeUART(void);

uint8_t SendByteUART(uint8_t data);

uint8_t SendStringUART(uint8_t *data);

uint8_t checkReceiveByteUART(void);

uint8_t ReceiveByteUART(void);

#endif
#endif
