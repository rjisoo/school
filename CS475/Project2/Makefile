CC = gcc
CFLAGS = -Wall -std=c99 -fopenmp -O2 -g
LDFLAGS = -lrt -lpthread -lm

TARGET = nbodies

INCLUDES =

SOURCE = main.c

.PHONY: all
all: default

.PHONY: default
default: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: debug
debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} -DDEBUG

.PHONY: fine-stat
fine-stat: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} -DFINE -DSTATIC

.PHONY: coarse-stat
coarse-stat: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} -DCOARSE -DSTATIC

.PHONY: fine-dyn
fine-dyn: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} -DFINE

.PHONY: coarse-dyn
coarse-dyn: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} -DCOARSE


.PHONY: clean
clean:
	@rm -f ${TARGET}
