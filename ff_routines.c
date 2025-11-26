#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ffioutil.h"

int ff_log_getclr(char* color, uint8_t p[8]) {
	int ret = 0;
	if((ret = ff_getclr(color, p)))
		fprintf(stderr, "Error: invalid color\n");
	return ret;
}

int ff_log_chkmagic(void) {
	int ret = 0;
	if((ret = ff_chkmagic()))
		fprintf(stderr, "ERROR: farbfeld magic value not present! The image may be corrupted.\n");
	return ret;
}

int ff_log_getpixel(uint8_t p[8]) {
	int ret = 0;
	if((ret =ff_getpixel(p)))
		fprintf(stderr, "ERROR: Early EOF!\n");
	return ret;
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
	ff_magic();

	ff_pn_nbo(width);
	ff_pn_nbo(height);

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
	ff_rect: add filled rectangle of given color to farbfeld image

SYNOPSIS:
	ff_rect x y width height color
*/
int ff_rect(
	uint32_t x, uint32_t y,
	uint32_t w, uint32_t h,
	uint8_t clr[8]
) {
	int ret = 0;
	if((ret = ff_log_chkmagic())) return ret;
	ff_magic();

	uint8_t p[8];

	/* Read image size (width and height) */
	if((ret = ff_log_getpixel(p))) return ret;
	uint32_t width = ff_scan2sz(p);
	uint32_t height = ff_scan2sz(p+4);
	ff_putpixel(p);

	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j) {
			if((ret = ff_log_getpixel(p))) return ret;
			if(in_rect(j, i, x, y, w, h))
				ff_putpixel(clr);
			else
				ff_putpixel(p);
		}

	return 0;
}

/*
NAME
	ff_rect: add filled ellipse of given color to farbfeld image

SYNOPSIS:
	ff_ellipse x y rx ry color
*/
int ff_ellipse(
	uint32_t x, uint32_t y,
	uint32_t rx, uint32_t ry,
	uint8_t clr[8]
) {
	int ret = 0;
	if((ret = ff_log_chkmagic())) return ret;
	ff_magic();

	uint8_t p[8];
	if((ret = ff_log_getpixel(p))) return ret;
	uint32_t width = ff_scan2sz(p);
	uint32_t height = ff_scan2sz(p+4);
	ff_putpixel(p);

	/* this very clearly overflows at r > 255 */
	uint16_t rx2 = rx*rx;
	uint16_t ry2 = ry*ry;
	uint32_t rx2y2 = rx2*ry2;
	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j) {
			if((ret = ff_log_getpixel(p))) return ret;
			uint32_t dx2r = j > x ? j - x : x - j;
			uint32_t dy2r = i > y ? i - y : y - i;
			dx2r *= dx2r; dy2r *= dy2r;
			dx2r *= ry2; dy2r *= rx2;

			if((dx2r + dy2r) <= rx2y2)
				ff_putpixel(clr);
			else
				ff_putpixel(p);
		}

	return 0;
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

	for(int i = 0; i < 4; ++i) {
		c[0][i] = (c[0][i] * (w - x) + (c[1][i] * x)) / w;
		c[2][i] = (c[2][i] * (w - x) + (c[3][i] * x)) / w;

		c[0][i] = (c[0][i] * (h - y)  + (c[2][i] * y)) / h;
	}
	ff_4clrfmtpix(c[0], p);
}

int ff_blip(
	uint32_t width, uint32_t height,
	uint8_t clrs[4][8]
) {
	uint8_t p[8] = {0};
	ff_magic();
	ff_pn_nbo(width);
	ff_pn_nbo(height);
	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j)
			blip(j, i, width, height, clrs, p), ff_putpixel(p);

	return 0;
}


