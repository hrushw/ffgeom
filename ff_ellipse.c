/*
NAME
	ff_rect: add filled ellipse of given color to farbfeld image

SYNOPSIS:
	ff_ellipse x y rx ry color
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ffioutil.h"

int ff_ellipse(int argc, char* argv[]) {
	ff_argchk(argc, 5, "Usage: ff_ellipse x y rx ry color\n");
	uint32_t x = strtol(argv[0], NULL, 0);
	uint32_t y = strtol(argv[1], NULL, 0);
	uint32_t rx = strtol(argv[2], NULL, 0);
	uint32_t ry = strtol(argv[3], NULL, 0);
	uint8_t clr[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF };
	ff_getclr_die(argv[4], clr);

	ff_chkmagic_die();
	ff_magic();

	uint8_t p[8];
	ff_getpixel_die(p);
	uint32_t width = ff_scan2sz(p);
	uint32_t height = ff_scan2sz(p+4);
	ff_putpixel(p);

	uint16_t rx2 = rx*rx;
	uint16_t ry2 = ry*ry;
	uint32_t rx2y2 = rx2*ry2;
	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j) {
			ff_getpixel_die(p);
			uint32_t dx2r = j > x ? j - x : x - j;
			uint32_t dy2r = i > y ? i - y : y - i;
			dx2r *= dx2r; dy2r *= dy2r;
			dx2r *= ry2; dy2r *= rx2;

			if((dx2r + dy2r) <= rx2y2)
				ff_putpixel(clr);
			else
				ff_putpixel(p);
		}

	exit(EXIT_SUCCESS);
}
