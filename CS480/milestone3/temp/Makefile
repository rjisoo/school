HEADERS = Parser.h
SOURCE = Parser.cpp
LEX = lex.l
CC = gcc
CXX = g++

default: scanner

lexer:
	lex $(LEX)

scanner: lexer
	$(CC) test.c lex.yy.c -o scanner

clean:
	@rm -f lex.yy.c
	@rm -f scanner