CC = gcc
CXX = g++
CFLAGS = -Wall -std=c99 -openmp -O3 -g -I.
CXXFLAGS = -Wall -openmp -O3 -g

TARGET = control

LDFLAGS = -lrt -lpthread 

INCLUDES =

SOURCE = control.c

default: all

all: control

control:
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

clean:
	@rm -f $(TARGET)
	
