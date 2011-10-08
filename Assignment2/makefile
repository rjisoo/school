default: prog

dynArray.o: dynArray.c dynArray.h 
	gcc -Wall -ansi -c src/dynArray.c	

prog: dynArray.o
	gcc -Wall -ansi -o binary/prog /binarydynArray.o src/stackapp.c
		
clean:
	rm binary/dynArray.o

cleanall: clean
	rm binary/prog
