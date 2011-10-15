default: prog

dynArray.o: src/dynArray.c src/dynArray.h 
	gcc -Wall -ansi -o binary/dynArray.o -c src/dynArray.c	

all: default

prog: dynArray.o
	gcc -Wall -ansi -o binary/prog binary/dynArray.o src/stackapp.c
		
clean: cleanall

cleanall:
	rm -f binary/*
