CC = g++
CFLAGS = -fopenmp -O3 -g -march=native -w
LDFLAGS = -lrt -lpthread -lm -lOpenCL -lglut -lGL -lGLU -lGLEW

TARGET = particle

INCLUDES = errorcodes.h

SOURCE = particle.cpp

.PHONY: all
all: default

.PHONY: default
default: ${SOURCE} ${INCLUDES} errorcodes
	${CC} ${CFLAGS} -I. ${SOURCE} -o ${TARGET} ${LDFLAGS} errorcodes.o

.PHONY: errorcodes
errorcodes: ${INCLUDES}
	${CC} -c ${CFLAGS} -I. errorcodes.cpp ${LDFLAGS}

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
