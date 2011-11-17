default: prog 

dynArray.o: src/dynArray.c src/dynArray.h src/type.h 
	gcc -Wall -ansi -o binary/dynArray.o -c src/dynArray.c

toDoList.o: src/toDoList.c src/toDoList.h src/type.h 
	gcc -Wall -ansi -o binary/toDoList.o -c src/toDoList.c

prog: dynArray.o toDoList.o src/main.c
	gcc -Wall -ansi -o binary/prog binary/dynArray.o binary/toDoList.o src/main.c

clean:
	rm binary/dynArray.o	
	rm binary/toDoList.o

cleanall: clean
	rm binary/prog
