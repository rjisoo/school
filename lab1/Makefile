SOURCE = lab1.c

CC = gcc
CXX = g++

CFLAGS = -Wall -std=c99 -openmp -O3 -g
CXXFLAGS = -Wall -openmp -O3 -g
#overkill on the flags, but that doesn't hurt anything
LDFLAGS = -lrt -lpthread

TARGET = lab1

INCLUDES = 

.PHONY: default
default: all

.PHONY: all
all:
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: clean
clean:
	@rm -f ${TARGET}
