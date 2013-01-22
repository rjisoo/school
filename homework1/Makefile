intel_CC = icc
intel_CXX = icpc
CFLAGS = -Wall -std=c99 -openmp -O3 -lm -g
CXXFLAGS = -Wall -openmp -O3 -g
#overkill on the flags, but that doesn't hurt anything
LDFLAGS = -lrt -lpthread 

#Get hostname for compiletime stuff
TMP = $(shell hostname)

ifeq ($(TMP),os-class.engr.oregonstate.edu)
	CC = icc
	CXX = icpc
else
	CC = gcc
	CXX = g++
endif


#replace this if you want to change the output name
TARGET = main

#any headers go here
INCLUDES = source/sieve.h

#any .c or .cpp files go here
SOURCE = source/main.c source/sieve.c
.PHONY: all
all:	default
#default is to compile
default:	compile

.PHONY: compile
#depends on all of you source and header files
compile: clean ${SOURCE} ${INCLUDES}
#this assumes you actually are linking all of the source files together
	${CC} ${CFLAGS} -I. ${SOURCE} -o binary/${TARGET} ${LDFLAGS}
	
.PHONY: debug
debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o binary/${TARGET} ${LDFLAGS} -DDEBUG

.PHONY: native
native: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -march=native -I. ${SOURCE} -o binary/${TARGET}.test ${LDFLAGS}
		
.PHONY: clean
clean:
	rm -rf binary/*
	
#.PHONY: test
#test:
#	@echo $(CC)
#	@echo $(CXX)