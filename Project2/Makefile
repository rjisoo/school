CC = gcc
CFLAGS = -Wall -std=c99 -fopenmp -O2 -g
LDFLAGS = -lrt -lpthread -lm

TARGET = nbodies

INCLUDES = nbodies.h

SOURCE = main.c

.PHONY: all
all: default

.PHONY: default
default: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: debug
debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} -DDEBUG


.PHONY: clean
clean:
	@rm -f ${TARGET}
