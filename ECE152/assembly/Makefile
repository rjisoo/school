TARGET = main

SRC = $(TARGET).asm

MCU = at90usb647

PROGRAM = dfu-programmer
PROGRAMFLAGS = $(MCU)
ERASE = erase
FLASH = flash "$(TARGET).hex"
START = start

CC = gavrasm
CFLAGS = -Bex
MSG_CLEANING = Cleaning project:
REMOVE = rm -f

all: clean
	./$(CC) $(CFLAGS) $(SRC)

clean:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).lst
	$(REMOVE) $(TARGET).asm~
	
program: all
	$(PROGRAM) $(PROGRAMFLAGS) $(ERASE)
	$(PROGRAM) $(PROGRAMFLAGS) $(FLASH)
	$(PROGRAM) $(PROGRAMFLAGS) $(START)

