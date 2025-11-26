CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wvla

CCOMP=$(CC) $(CFLAGS)

OBJS=ffioutil.o ff_routines.o

all: test

test: test.c ff_routines.c ffioutil.c ff_routines.h ffioutil.h ffioutil.c
	$(CCOMP) test.c ff_routines.c ffioutil.c -o test

ff_routines.o: ff_routines.c ff_routines.h ffioutil.h
	$(CCOMP) ff_routines.c -c -o ff_routines.o

ffioutil.o: ffioutil.c ffioutil.h
	$(CCOMP) ffioutil.c -c -o ffioutil.o

clean:
	rm -f *.o test
