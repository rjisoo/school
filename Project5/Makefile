CC = g++
CFLAGS = -fopenmp -O3 -g -march=native -w
LDFLAGS = -lrt -lpthread -lm -lOpenCL

TARGET = first

INCLUDES = errorcodes.h

SOURCE = first.cpp

.PHONY: all
all: default

.PHONY: default
default: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: global
global: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} -D"LOCAL=32" -D"GLOBAL=8192"

.PHONY: local
local: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS}

.PHONY: clean
clean:
	@rm -f ${TARGET}
	@rm -f printinfo
	@rm -f *.o

.PHONY: print
print:
	${CC} ${CFLAGS} -I. printinfo.cpp -o printinfo ${LDFLAGS}
