#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <stdint.h>
#include "ffioutil.h"
#include "ff_routines.h"

void ff_wrap_init(int argc, char* argv[]) {
	ff_argchk(argc, 3, "Usage: ff_init width height color\n");
	uint32_t width = strtol(argv[0], NULL, 0);
	uint32_t height = strtol(argv[1], NULL, 0);
	uint8_t clr[8] = FF_COLOR_BASE;
	ff_getclr_die(argv[2], clr);

	ff_init(width, height, clr);
}

void ff_wrap_rect(int argc, char* argv[]) {
	ff_argchk(argc, 5, "Usage: ff_rect x y width height color\n");
	uint32_t x = strtol(argv[0], NULL, 0);
	uint32_t y = strtol(argv[1], NULL, 0);
	uint32_t w = strtol(argv[2], NULL, 0);
	uint32_t h = strtol(argv[3], NULL, 0);
	uint8_t clr[8] = FF_COLOR_BASE;
	ff_getclr_die(argv[4], clr);

	ff_rect(x, y, w, h, clr);
}

void ff_wrap_blip(int argc, char* argv[]) {
	ff_argchk(argc, 6, "Usage: ff_blip width height color0 color1 color2 color3\n");
	uint32_t width = strtol(argv[0], NULL, 0);
	uint32_t height = strtol(argv[1], NULL, 0);
	uint8_t clrs[4][8] = { FF_COLOR_BASE, FF_COLOR_BASE, FF_COLOR_BASE, FF_COLOR_BASE };
	ff_getclr_die(argv[2], clrs[0]);
	ff_getclr_die(argv[3], clrs[1]);
	ff_getclr_die(argv[4], clrs[2]);
	ff_getclr_die(argv[5], clrs[3]);

	ff_blip(width, height, clrs);
}

void ff_wrap_ellipse(int argc, char* argv[]) {
	ff_argchk(argc, 5, "Usage: ff_ellipse x y rx ry color\n");
	uint32_t x = strtol(argv[0], NULL, 0);
	uint32_t y = strtol(argv[1], NULL, 0);
	uint32_t rx = strtol(argv[2], NULL, 0);
	uint32_t ry = strtol(argv[3], NULL, 0);
	uint8_t clr[8] = FF_COLOR_BASE;
	ff_getclr_die(argv[4], clr);

	ff_ellipse(x, y, rx, ry, clr);
}

int main(int argc, char* argv[]) {
	if(argc < 2) return fprintf(stderr, "Usage: ffgeom [-i file] [operation] [args]\n"), -1;

	if(!strcmp(argv[1], "init"))
		ff_wrap_init(argc-2, argv+2);
	else if(!strcmp(argv[1], "rect"))
		ff_wrap_rect(argc-2, argv+2);
	else if(!strcmp(argv[1], "blip"))
		ff_wrap_blip(argc-2, argv+2);
	else if(!strcmp(argv[1], "ellipse"))
		ff_wrap_ellipse(argc-2, argv+2);

	return 0;
}
