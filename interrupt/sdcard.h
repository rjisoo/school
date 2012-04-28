#ifndef SDCARD_H
#define SDCARD_H

void printErrorUART(uint8_t err);

uint8_t initializeFAT(FATFS* fs);

#endif
