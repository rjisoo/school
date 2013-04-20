C_SOURCE = lab1.c

CC = gcc
CXX = g++

CFLAGS = -Wall -std=c99 -openmp -O3 -g -lm
CXXFLAGS = -Wall -openmp -O3 -g
#overkill on the flags, but that doesn't hurt anything
LDFLAGS = -lrt -lpthread

TARGET = lab1

INCLUDES = 

.PHONY: default
default: all

.PHONY: all
all: compile pdf

.PHONY: compile
compile:
	${CC} ${CFLAGS} -I. ${C_SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: dvi
dvi: ${TARGET}.tex
	latex ${TARGET}.tex
	latex ${TARGET}.tex

.PHONY: ps
ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

.PHONY: pdf
pdf: ps
	ps2pdf ${TARGET}.ps

.PHONY: clean
clean:
	@rm -f ${TARGET}
