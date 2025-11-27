#include <stdint.h>
#include "ffioutil.h"

void blip (
	uint32_t x, uint32_t y, uint32_t w, uint32_t h,
	uint8_t clrs[4][8], uint8_t p[8]
) {
	uint16_t c[4][4] = {{0}};
	uint8_t i;

	for(i = 0; i < 4; ++i) ff_pixfmt4clr(clrs[i], c[i]);

	for(i = 0; i < 4; ++i)
		c[0][i] = (
			( (c[0][i] * (w - x)) + (c[1][i] * x) ) * (h - y) +
			( (c[2][i] * (w - x)) + (c[3][i] * x) ) * y
		) / (w * h);

	ff_4clrfmtpix(c[0], p);
}

/* ff_blip (width height color0 color1 color2 color3)
 * generate gradient using corner colors and bilinear interpolation */
int ff_blip (
	int fd,
	uint32_t width, uint32_t height,
	uint8_t clrs[4][8]
) {
	uint32_t y, x;
	uint8_t p[8] = {0};

	ff_header_init(fd, width, height);
	for(y = 0; y < height; ++y)
		for(x = 0; x < width; ++x)
			blip(x, y, width, height, clrs, p), ff_putpixel(fd, p);

	return 0;
}
