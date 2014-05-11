CC = gcc
CFLAGS = -fopenmp -O2 -g
LDFLAGS = -lrt -lpthread -lm

TARGET = simulation

INCLUDES = simulation.h

SOURCE = main.c

.PHONY: all
all: default

.PHONY: default
default: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: clean
clean:
	@rm -f ${TARGET}
