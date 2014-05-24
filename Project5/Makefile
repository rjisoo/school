CC = g++
CFLAGS = -fopenmp -O3 -g -march=native
LDFLAGS = -lrt -lpthread -lm -lOpenCL

TARGET = first

INCLUDES =

SOURCE = first.cpp

.PHONY: all
all: default

.PHONY: default
default: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: clean
clean:
	@rm -f ${TARGET}

.PHONY: print
print:
	${CC} ${CFLAGS} -I. printinfo.cpp -o printinfo ${LDFLAGS}
