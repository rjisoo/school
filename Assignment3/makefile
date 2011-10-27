default: all
all:
	gcc -Wall -ansi -o binary/type.h.gch src/type.h
	gcc -Wall -ansi -o binary/listbag.h.gch src/listbag.h
	gcc -Wall -ansi -o binary/listbag.o -c src/listbag.c
	gcc -Wall -ansi -o binary/list.o -c src/list.c
	gcc -Wall -ansi -o binary/main src/main.c binary/listbag.o binary/list.o

clean:
	rm binary/listbag.o
	rm binary/list.o
	rm binary/listbag.h.gch
	rm binary/type.h.gch