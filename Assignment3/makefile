default: all
all:
	gcc -Wall -ansi src/type.h
	gcc -Wall -ansi src/listbag.h
	gcc -Wall -ansi -o binary/listbag.o -c src/listbag.c
	gcc -Wall -ansi -o binary/list.o -c src/list.c
	gcc -Wall -ansi -o binary/main src/main.c binary/listbag.o binary/list.o

clean:
	rm -rf binary/*
	rm src/*.h.gch
