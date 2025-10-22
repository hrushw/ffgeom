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

int ff_rect(int argc, char* argv[]) {
	if(argc < 5) {
		fprintf(stderr, "Usage: ff_rect x y width height color\n");
		return -1;
	}
	uint32_t x = strtol(argv[0], NULL, 0);
	uint32_t y = strtol(argv[1], NULL, 0);
	uint32_t w = strtol(argv[2], NULL, 0);
	uint32_t h = strtol(argv[3], NULL, 0);
	uint8_t clr[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF };
	ff_getclr_die(argv[4], clr);

	/* Do not check farbfeld magic value */
	if(ff_chkmagic())
		return fprintf(stderr, "ERROR: farbfeld magic value not present! The image may be corrupted.\n"), -1;
	ff_magic();

	uint8_t p[8];

	/* Read image size (width and height) */
	ff_getpixel_die(p);
	uint32_t width = ff_scan2sz(p);
	uint32_t height = ff_scan2sz(p);
	ff_putpixel(p);

	for(uint32_t i = 0; i < height; ++i) {
		for(uint32_t j = 0; j < width; ++j) {
			ff_getpixel_die(p);
			if(i >= y && j >= x && (i - y) < h && (j - x) < w)
				ff_putpixel(clr);
			else
				ff_putpixel(p);
		}
	}

	return 0;
}
