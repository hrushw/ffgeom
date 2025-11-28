CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wvla
IFLAGS=-I .
CCOMP=$(CC) $(CFLAGS) $(IFLAGS)

OBJS=ffioutil.o routines/rect.o routines/blip.o routines/overlay.o
FFIOUTIL=ffioutil.c ffioutil.h

all: $(OBJS)

TESTCOMP_CMD=$(CCOMP) $@.o $(OBJS) -o $@

test0: test0.c $(OBJS)
	$(CCOMP) -c $@.c -o $@.o
	$(TESTCOMP_CMD)

test1: test1.c $(OBJS)
	$(CCOMP) -c $@.c -o $@.o
	$(TESTCOMP_CMD)

.c.o:
	$(CCOMP) -c $< -o $@

ffioutil.o: $(FFIOUTIL)
	$(CCOMP) ffioutil.c -c -o $@

clean:
	rm -f *.o routines/*.o test0 test1

.PHONY: all clean
