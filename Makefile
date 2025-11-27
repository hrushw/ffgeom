CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wvla
IFLAGS=-I .
CCOMP=$(CC) $(CFLAGS) $(IFLAGS)

OBJS=ffioutil.o routines/rect.o routines/blip.o routines/overlay.o
TESTS=tests/test0
FFIOUTIL=ffioutil.c ffioutil.h

all: $(OBJS)

test: tests/test0

routines/rect.o: routines/rect.c $(FFIOUTIL)
	$(CCOMP) -c routines/rect.c -o routines/rect.o

routines/blip.o: routines/blip.c $(FFIOUTIL)
	$(CCOMP) -c routines/blip.c -o routines/blip.o

routines/overlay.o: routines/overlay.c $(FFIOUTIL)
	$(CCOMP) -c routines/overlay.c -o routines/overlay.o

tests/test0: tests/test0.c $(OBJS)
	$(CCOMP) tests/test0.c -c -o tests/test0.o
	$(CCOMP) tests/test0.o $(OBJS) -o tests/test0

ffioutil.o: $(FFIOUTIL)
	$(CCOMP) ffioutil.c -c -o ffioutil.o

clean:
	rm -f *.o routines/*.o test
