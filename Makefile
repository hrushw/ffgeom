CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wvla
IFLAGS=-I .

CCOMP=$(CC) $(CFLAGS) $(IFLAGS)

OBJS=ffioutil.o routines/rect.o routines/blip.o routines/overlay.o

all: $(OBJS)

routines/rect.o: routines/rect.c ffioutil.h ffioutil.c
	$(CCOMP) -c routines/rect.c -o routines/rect.o

routines/blip.o: routines/blip.c ffioutil.h ffioutil.c
	$(CCOMP) -c routines/blip.c -o routines/blip.o

routines/overlay.o: routines/overlay.c ffioutil.h ffioutil.c
	$(CCOMP) -c routines/overlay.c -o routines/overlay.o

test: test.c ff_routines.c ffioutil.c ff_routines.h ffioutil.h
	$(CCOMP) test.c ff_routines.c ffioutil.c -o test

ffioutil.o: ffioutil.c ffioutil.h
	$(CCOMP) ffioutil.c -c -o ffioutil.o

clean:
	rm -f *.o test
