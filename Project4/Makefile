CC = gcc
CFLAGS = -Wall -std=c99 -fopenmp -O2 -g
LDFLAGS = -lrt -lpthread -lm

TARGET = simulation

INCLUDES =

SOURCE = main.c

.PHONY: all
all: default

.PHONY: default
default: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: numthread
numthread: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} -D'NUM=0' -D'NUMT=2'


.PHONY: clean
clean:
	@rm -f ${TARGET}
