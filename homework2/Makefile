#Get hostname for compiletime stuff
HOST = $(shell hostname)

ifeq ($(HOST),os-class.engr.oregonstate.edu)
	CC = icc
	CXX = icpc
else
	CC = gcc
	CXX = g++
endif

CFLAGS = -Wall -std=c99 -openmp -O3 -g
CXXFLAGS = -Wall -openmp -O3 -g
#overkill on the flags, but that doesn't hurt anything
LDFLAGS = -lrt -lpthread 

#replace this if you want to change the output name
TARGET = myar

#any headers go here
INCLUDES =

#any .c or .cpp files go here
SOURCE = myar.c

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
	rm ${TARGET}{.out,.log,.aux,.c.tex,.pdf,} 

.PHONY: pdf
pdf: 	pygment
	pdflatex ${TARGET}.tex

.PHONY: pygment
pygment:
	pygmentize -f latex -o ${SOURCE}.tex ${SOURCE}	
#.PHONY: test
#test:
#	@echo $(CC)
#	@echo $(CXX)
