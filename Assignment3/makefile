default: all
all:
	gcc -Wall -ansi -o binary/type.h.gch src/type.h
	gcc -Wall -ansi -o binary/dynArray.h.gch src/dynArray.h
	gcc -Wall -ansi -o binary/dynArray.o -c src/dynArray.c
	gcc -Wall -ansi -o binary/dynArrayBag.o -c src/list.c
	gcc -Wall -ansi -o binary/main src/main.c binary/dynArrayBag.o binary/dynArray.o

clean:
	rm binary/*