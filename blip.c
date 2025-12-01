#include <stdint.h>
#include "ffioutil.h"

void blip (
	uint16_t x, uint16_t y, uint16_t w, uint16_t h,
	uint16_t c[4][4], uint8_t p[8]
) {
	uint16_t c_[4] = {0};
	uint8_t i;

	for(i = 0; i < 4; ++i) {
		uint32_t c0 = ((c[0][i] * (w - x)) + (c[1][i] * x)) ;
		uint32_t c1 = ((c[2][i] * (w - x)) + (c[3][i] * x)) ;

		c_[i] = (
			(c0 * (h - y)) +
			(c1 * y)
		) / (w*h);
	}

	ff_4clrfmtpix(c_, p);
}

/* ff_blip (width height color0 color1 color2 color3)
 * generate gradient using corner colors and bilinear interpolation */
int ff_blip (
	int fd,
	uint32_t width, uint32_t height,
	uint8_t clrs[4][8]
) {
	uint32_t y, x;
	uint16_t c[4][4] = {{0}};
	uint8_t p[8] = {0};
	uint8_t i;

	if(width > UINT16_MAX || height > UINT32_MAX) return -1;
	for(i = 0; i < 4; ++i) ff_pixfmt4clr(clrs[i], c[i]);

	ff_header_init(fd, width, height);
	for(y = 0; y < height; ++y)
		for(x = 0; x < width; ++x)
			blip(x, y, width, height, c, p), ff_putpixel(fd, p);

	return 0;
}
