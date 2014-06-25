CC = gcc
CXX = g++
CFLAGS = -Wall -std=c99 -fopenmp
CXXFLAGS= -Wall -fopenmp
LDFLAGS = -lrt -lpthread -lm

TARGET = arraymult

INCLUDES =

SOURCE = ${TARGET}.cpp

.PHONY: all
all: default

.PHONY: default
default: simd ${SOURCE} ${INCLUDES}
	${CXX} ${CXXFLAGS} -I. ${SOURCE} simd.o -o ${TARGET} ${LDFLAGS}

.PHONY: simd
simd: simd.cpp simd.h
	${CXX} -c simd.cpp -o simd.o

.PHONY: clean
clean:
	@rm -f ${TARGET}
	@rm -f *.o

