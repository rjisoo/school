regular_CC = gcc
regular_CXX = g++
intel_CC = icc
intel_CXX = icpc
CFLAGS = -Wall -std=c99 -openmp -O3 -g -I.
CXXFLAGS = -Wall -openmp -O3 -g
#overkill on the flags, but that doesn't hurt anything
LDFLAGS = -lrt -lpthread 

TMP = $(shell host)

#replace this if you want to change the output name
TARGET = example

#any headers go here
INCLUDES = 

#any .c or .cpp files go here
SOURCE = source/main.c

#default is to compile
default:	compile_gcc

.PHONY: compile_intel
#depends on all of you source and header files
compile_intel: ${SOURCE} ${INCLUDES}
#this assumes you actually are linking all of the source files together
	${intel_CC} ${CFLAGS} ${SOURCE} -o binary/${TARGET} ${LDFLAGS}

.PHONY: intel_debug
intel_debug: ${SOURCE} ${INCLUDES}
	${intel_CC} ${CFLAGS} ${SOURCE} -o binary/${TARGET} ${LDFLAGS} -DDEBUG
	
.PHONY: compile_gcc
compile_gcc: $(SOURCE) $(INCLUDES)
	$(regular_CC) ${CFLAGS} ${SOURCE} -o binary/${TARGET} ${LDFLAGS}

.PHONY: regular_debug
regular_debug:
	$(regular_CC) ${CFLAGS} ${SOURCE} -o binary/${TARGET} ${LDFLAGS} -DDEBUG
	
.PHONY: clean
clean:
	rm -rf binary/*
	
.PHONY: test
test:
	@echo $(TMP)