default: all
all: type

type: list
	gcc -Wall -ansi -o binary/type.h.gch src/type.h
	gcc -Wall -ansi -o binary/listbag.h.gch src/listbag.h
	gcc -Wall -ansi -o binary/dynArray.h.gch src/dynArray.h
	gcc -Wall -ansi -c binary/cirListDeque.h.gch src/cirListDeque.h

list:dynArr
	gcc -Wall -ansi -o binary/list.o -c src/list.c
	gcc -Wall -ansi -o binary/listbag.o -c src/listbag.c
	gcc -Wall -ansi -o binary/mainlist src/main.list.c binary/list.o binary/listbag.o
	
dynArr: cirListDeque
	gcc -Wall -ansi -o binary/dynArray.o -c src/dynArray.c
	gcc -Wall -ansi -o binary/dynArrayBag.o -c src/dynArrayBag.c
	gcc -Wall -ansi -o binary/mainarr src/main.dynArr.c binary/dynArray.o binary/dynArrayBag.o
	
cirListDeque:
	gcc -Wall -ansi cirListDeque.h
	gcc -Wall -ansi -o binary/cirListDeque.o -c cirListDeque.c
	gcc -Wall -ansi -o binary/maincir src/main.cir.c binary/cirListDeque.o
	

clean:
	rm binary/*
	