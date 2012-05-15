#ifndef wunderbard_h
#define wunderboard_h

uint8_t clearArray(void);

uint8_t setArrayAmber(uint8_t rows);

uint8_t setArrayGreen(uint8_t rows);

uint8_t setArrayRed(uint8_t rows);

uint8_t initWunderboard(void);

uint8_t visualUpDown(uint8_t direction);

uint8_t itoa(uint8_t* string, uint8_t number);

#endif
