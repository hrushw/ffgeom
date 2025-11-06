CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wvla

CCOMP=$(CC) $(CFLAGS)

OBJS=ffgeom.o ffioutil.o ff_wraps.o ff_routines.o

all: ffgeom

ff_routines.o: ff_routines.c ffioutil.h
	$(CCOMP) ff_routines.c -c -o ff_routines.o

ff_wraps.o: ff_wraps.c ffioutil.h
	$(CCOMP) ff_wraps.c -c -o ff_wraps.o

ffioutil.o: ffioutil.c ffioutil.h
	$(CCOMP) ffioutil.c -c -o ffioutil.o

ffgeom.o: ffgeom.c ffioutil.h
	$(CCOMP) ffgeom.c -c -o ffgeom.o

ffgeom: $(OBJS)
	$(CC) $(OBJS) -o ffgeom

clean:
	rm -f *.o ffgeom
