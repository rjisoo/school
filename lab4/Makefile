SRC = main.c
DEST = test

CC = gcc

default: all

all: main

cache.o: cache.c cache.h
	$(CC) -c cache.c

main:
	$(CC) $(SRC) -o $(DEST) -O1

clean:
	@rm -f $(DEST) cache.o	
