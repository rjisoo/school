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
TARGET = uniqify

#any headers go here
INCLUDES =

#any .c or .cpp files go here
SOURCE = uniqify.cpp

.PHONY: all
all: default

#default is to compile
default:	c pdf

.PHONY: c
#depends on all of you source and header files
c: ${SOURCE} ${INCLUDES}
#this assumes you actually are linking all of the source files together
	${CXX} ${CXFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}
	
.PHONY: debug
debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS} -DDEBUG

.PHONY: dvi
dvi: ${TARGET}.tex 
#	pygmentize the input source file -- THIS NAME SHOULD BE SAFE
	pygmentize -f latex -o __${SOURCE}.tex ${SOURCE}
#	run latex twice to get references correct
	latex ${TARGET}.tex
#	you can also have a bibtex line here
#	bibtex $(TARGET).tex
	latex $(TARGET).tex
#	remove the pygmentized output to avoid cluttering up the directory
	rm __${SOURCE}.tex

.PHONY: ps	
ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps
	
.PHONY: pdf ${TARGET}.tex
pdf: ps
	ps2pdf ${TARGET}.ps
	
.PHONY: clean
clean:
	@rm -f ${TARGET}{.dvi,.ps,.out,.log,.aux,.c.tex,}

#.PHONY: test
#test:
#	@echo $(CC)
#	@echo $(CXX)
