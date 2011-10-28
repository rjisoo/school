default: all
all: dynArr
	gcc -Wall -ansi -o binary/type.h.gch src/type.h
	gcc -Wall -ansi -o binary/listbag.h.gch src/listbag.h
	gcc -Wall -ansi -o binary/list.o -c src/list.c
	gcc -Wall -ansi -o binary/listbag.o -c src/listbag.c
	gcc -Wall -ansi -o binary/main.list src/main.c binary/list.o binary/listbag.o
	
dynArr:
	gcc -Wall -ansi -o binary/type.h.gch src/type.h
	gcc -Wall -ansi -o binary/dynArray.h.gch src/dynArray.h
	gcc -Wall -ansi -o binary/dynArray.o -c src/dynArray.c
	gcc -Wall -ansi -o binary/dynArrayBag.o -c src/dynArrayBag.c
	gcc -Wall -ansi -o binary/main.array src/main.dynArr.c binary/dynArrayBag.o binary/dynArray.o

clean:
	rm binary/*