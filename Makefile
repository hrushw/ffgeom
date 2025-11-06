CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wvla

CCOMP=$(CC) $(CFLAGS)

OBJS=ffgeom.o ffioutil.o ff_wraps.o ff_init.o ff_rect.o ff_blip.o ff_ellipse.o

all: ffgeom

ff_init.o: ff_init.c ffioutil.h
	$(CCOMP) ff_init.c -c -o ff_init.o

ff_rect.o: ff_rect.c ffioutil.h
	$(CCOMP) ff_rect.c -c -o ff_rect.o

ff_ellipse.o: ff_ellipse.c ffioutil.h
	$(CCOMP) ff_ellipse.c -c -o ff_ellipse.o

ff_blip.o: ff_blip.c ffioutil.h
	$(CCOMP) ff_blip.c -c -o ff_blip.o

ff_wraps.o: ff_wraps.c ffioutil.h
	$(CCOMP) ff_wraps.c -c -o ff_wraps.o

ffioutil.o: ffioutil.c ffioutil.h
	$(CCOMP) ffioutil.c -c -o ffioutil.o

ffgeom.o: ffgeom.c ffioutil.h
	$(CCOMP) ffgeom.c -c -o ffgeom.o

ffgeom: $(OBJS)
	$(CC) $(OBJS) -o ffgeom

clean:
	rm $(OBJS) ffgeom
