CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wvla
IFLAGS=-I .
CCOMP=$(CC) $(CFLAGS) $(IFLAGS)

OBJS=ffioutil.o rect.o blip.o overlay.o
FFIOUTIL=ffioutil.c ffioutil.h

all: $(OBJS)

TESTCOMP_CMD=$(CCOMP) $@.o $(OBJS) -o $@

test: test.c $(OBJS)
	$(CCOMP) -c $@.c -o $@.o
	$(TESTCOMP_CMD)
	./$@ | ff2png >| test.png

.c.o:
	$(CCOMP) -c $< -o $@

ffioutil.o: $(FFIOUTIL)
	$(CCOMP) ffioutil.c -c -o $@

clean:
	rm -f *.o routines/*.o test test.png

.PHONY: all clean
