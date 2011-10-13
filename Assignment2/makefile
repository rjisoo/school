default: prog

dynArray.o: src/dynArray.c src/dynArray.h 
	gcc -Wall -ansi -o binary/dynArray.o -c src/dynArray.c	

all: dynArray.o
	gcc -Wall -ansi -o binary/main binary/dynArray.o src/main.c

prog: dynArray.o
	gcc -Wall -ansi -o binary/prog binary/dynArray.o src/stackapp.c
		
clean: cleanall
	rm binary/dynArray.o

cleanall: clean
	rm -f binary/*
