/*
NAME
	ff_blip - generate gradient using corner colors and bilinear interpolation

SYNOPSIS
	ff_blip width height color0 color1 color2 color3
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ffioutil.h"

void blip(
	uint32_t x, uint32_t y, uint32_t w, uint32_t h,
	uint8_t clrs[4][8], uint8_t p[8]
) {
	uint16_t c[4][4] = {{0}};
	for(int i = 0; i < 4; ++i) ff_pixfmt4clr(clrs[i], c[i]);

	for(int i = 0; i < 4; ++i) {
		c[0][i] = (c[0][i] * (w - x) + (c[1][i] * x)) / w;
		c[2][i] = (c[2][i] * (w - x) + (c[3][i] * x)) / w;

		c[0][i] = (c[0][i] * (h - y)  + (c[2][i] * y)) / h;
	}
	ff_4clrfmtpix(c[0], p);
}

void ff_blip(
	uint32_t width, uint32_t height,
	uint8_t clrs[4][8]
) {
	uint8_t p[8] = FF_COLOR_BASE;
	ff_magic();
	ff_pn_nbo(width);
	ff_pn_nbo(height);
	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j)
			blip(j, i, width, height, clrs, p), ff_putpixel(p);
}


