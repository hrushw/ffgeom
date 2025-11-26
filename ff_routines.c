#include <stdint.h>

#include "ffioutil.h"

void ff_header_init(uint32_t width, uint32_t height) {
	ff_magic();
	ff_pn_nbo(width);
	ff_pn_nbo(height);
}

/*
NAME
	ff_init - print farbfeld image with given dimensions and color to stdout

SYNOPSIS
	ff_init width height color
*/
int ff_init(
	uint32_t width, uint32_t height,
	uint8_t clr[8]
) {
	ff_header_init(width, height);

	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j)
			ff_putpixel(clr);

	return 0;
}

static inline int in_rect(uint32_t x, uint32_t y, uint32_t x0, uint32_t y0, uint32_t w, uint32_t h) {
	return x >= x0 && y >= y0 && (x - x0) < w && (y - y0) < h;
}

/*
NAME
	ff_blip - generate gradient using corner colors and bilinear interpolation

SYNOPSIS
	ff_blip width height color0 color1 color2 color3
*/
void blip(
	uint32_t x, uint32_t y, uint32_t w, uint32_t h,
	uint8_t clrs[4][8], uint8_t p[8]
) {
	uint16_t c[4][4] = {{0}};
	for(int i = 0; i < 4; ++i) ff_pixfmt4clr(clrs[i], c[i]);

	for(int i = 0; i < 4; ++i)
		c[0][i] = (
			( (c[0][i] * (w - x)) + (c[1][i] * x) ) * (h - y) +
			( (c[2][i] * (w - x)) + (c[3][i] * x) ) * y
		) / (w * h);

	ff_4clrfmtpix(c[0], p);
}

int ff_blip(
	uint32_t width, uint32_t height,
	uint8_t clrs[4][8]
) {
	ff_header_init(width, height);

	uint8_t p[8] = {0};
	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j)
			blip(j, i, width, height, clrs, p), ff_putpixel(p);

	return 0;
}


