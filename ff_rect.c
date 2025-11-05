/*
NAME
	ff_rect: add filled rectangle of given color to farbfeld image

SYNOPSIS:
	ff_rect x y width height color
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ffioutil.h"

void ff_rect_(
	uint32_t x, uint32_t y,
	uint32_t w, uint32_t h,
	uint8_t clr[8]
) {
	ff_chkmagic_die();
	ff_magic();

	uint8_t p[8];

	/* Read image size (width and height) */
	ff_getpixel_die(p);
	uint32_t width = ff_scan2sz(p);
	uint32_t height = ff_scan2sz(p+4);
	ff_putpixel(p);

	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j) {
			ff_getpixel_die(p);
			if(i >= y && j >= x && (i - y) < h && (j - x) < w)
				ff_putpixel(clr);
			else
				ff_putpixel(p);
		}
}

void ff_rect(int argc, char* argv[]) {
	ff_argchk(argc, 5, "Usage: ff_rect x y width height color\n");
	uint32_t x = strtol(argv[0], NULL, 0);
	uint32_t y = strtol(argv[1], NULL, 0);
	uint32_t w = strtol(argv[2], NULL, 0);
	uint32_t h = strtol(argv[3], NULL, 0);
	uint8_t clr[8] = FF_COLOR_BASE;
	ff_getclr_die(argv[4], clr);

	ff_rect_(x, y, w, h, clr);
}
