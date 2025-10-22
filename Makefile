CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wvla

CCOMP=$(CC) $(CFLAGS)

OBJS=main.o ffioutil.o ff_init.o ff_rect.o ff_blip.o

all: ffgeom

ff_init.o: ff_init.c ffioutil.h
	$(CCOMP) ff_init.c -c -o ff_init.o

ff_rect.o: ff_rect.c ffioutil.h
	$(CCOMP) ff_rect.c -c -o ff_rect.o

ff_blip.o: ff_blip.c ffioutil.h
	$(CCOMP) ff_blip.c -c -o ff_blip.o

ffioutil.o: ffioutil.c ffioutil.h
	$(CCOMP) ffioutil.c -c -o ffioutil.o

main.o: main.c ffioutil.h
	$(CCOMP) main.c -c -o main.o

ffgeom: $(OBJS)
	$(CC) $(OBJS) -o ffgeom

clean:
	rm $(OBJS) ffgeom
