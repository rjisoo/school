#include "sdcard.h"

/// Success error code
#define ERR_NONE 0x00

/// Failed to mount SDC/MMC error code
#define ERR_FMOUNT 0x01

/// No SDC/MMC present error code
#define ERR_NODISK 0x02

/// Unable to initialize FAT file system error code
#define ERR_NOINIT 0x03

/// MMC/SDC write protected error code
#define ERR_PROTECTED 0x04

#define ERR_FOPEN 0x05
#define ERR_TIMER 0x06
#define ERR_FWRITE 0x07
#define ERR_FULL 0x08
#define ERR_FCLOSE 0x09


void printErrorUART(uint8_t err) {
	switch (err) {
	case ERR_FMOUNT:
		while (SendStringUART("ERROR: Could not mount SDC/MMC\r\n") == 1);
		break;
	case ERR_NODISK:
		while (SendStringUART("ERROR: No SDC/MMC present\r\n") == 1);
		break;
	case ERR_NOINIT:
		while (SendStringUART("ERROR: Unable to initialize FAT file system\r\n")== 1);
		break;
	case ERR_PROTECTED:
		while (SendStringUART("ERROR: SDC/MMC is write protected\r\n") == 1);
		break;
	case ERR_FOPEN:
		while (SendStringUART("ERROR: Unable to open file\r\n") == 1);
		break;
	case ERR_TIMER:
		while (SendStringUART(
				"ERROR: Clock selector for TIMER/COUNTER0 is invalid\r\n") == 1);
		break;
	case ERR_FWRITE:
		while (SendStringUART("ERROR: Unable to write to file\r\n") == 1);
		break;
	case ERR_FULL:
		while (SendStringUART("ERROR: File system is full\r\n") == 1);
		break;
	case ERR_FCLOSE:
		while (SendStringUART("ERROR: Unable to close file\r\n") == 1);
		break;
	default:
		while (SendStringUART("ERROR: Unknown\r\n") == 1);
		break;
	}
}

uint8_t initializeFAT(FATFS* fs) {
	DSTATUS driveStatus;

	// Mount and verify disk type
	if (f_mount(0, fs) != FR_OK) {
		// Report error
		return ERR_FMOUNT;
	}

	driveStatus = disk_initialize(0);

	// Verify that disk exists
	if (driveStatus & STA_NODISK) {
		// Report error
		return ERR_NODISK;
	}

	// Verify that disk is initialized
	if (driveStatus & STA_NOINIT) {
		// Report error
		return ERR_NOINIT;
	}

	// Verify that disk is not write protected
	if (driveStatus & STA_PROTECT) {
		// Report error
		return ERR_PROTECTED;
	}

	return ERR_NONE;
}
