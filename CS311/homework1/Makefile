intel_CC = icc
intel_CXX = icpc
CFLAGS = -Wall -std=c99 -openmp -O3 -g
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
INCLUDES = sieve.h

#any .c or .cpp files go here
SOURCE = main.c sieve.c

.PHONY: all
all: compile

#default is to compile
default:	compile

.PHONY: compile
#depends on all of you source and header files
compile: ${SOURCE} ${INCLUDES}
#this assumes you actually are linking all of the source files together
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}
	
.PHONY: debug
debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS} -DDEBUG
		
.PHONY: clean
clean:
	rm main
	
#.PHONY: test
#test:
#	@echo $(CC)
#	@echo $(CXX)
