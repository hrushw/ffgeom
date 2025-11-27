#include <stdint.h>
#include "ffioutil.h"

/* ff_rect (width height color)
 * print farbfeld image with given dimensions and color to stdout */
#define FF_OVERLAY_CROP 0x1

#define HEX_4 0x10000
#define HEX_8 0x100000000

void overlay(uint8_t p0[8], uint8_t p1[8], uint8_t p[8]) {
	uint16_t c[2][4] = {{0}};

	ff_pixfmt4clr(p0, c[0]);
	ff_pixfmt4clr(p1, c[1]);

	/* blend colors */
	uint32_t a1a2 = c[0][3] * c[1][3];

	for(uint8_t i = 0; i < 3; ++i)
		c[0][i] = (
			( (c[0][i]*c[0][3] + c[1][i]*c[1][3]) * HEX_4 ) -
			c[0][i] * a1a2
		) / HEX_8;

	/* new alpha */
	c[0][3] = (
		((c[0][3] + c[1][3]) * HEX_4) - a1a2
	) / HEX_4;

	ff_4clrfmtpix(c[0], p);
}

int ff_overlay (
	int basefd, int layerfd, int outfd,
	uint32_t x0, uint32_t y0
) {
	uint32_t basew, baseh, layerw, layerh, y, x;
	uint64_t yskip;
	uint32_t xskip;
	uint8_t p[8] = {0};
	uint8_t lp[8] = {0};
	int ycheck;

	ff_chkmagic(basefd);
	ff_getsz(basefd, &basew, &baseh);

	ff_chkmagic(layerfd);
	ff_getsz(layerfd, &layerw, &layerh);

	xskip = x0 + layerw > basew ?
		x0 + layerw - basew : 0;
	yskip = y0 + layerh > baseh ?
		(y0 + layerh - baseh) * layerw : 0;

	for(y = 0; y < baseh; ++y) {
		ycheck = (y >= y0 && (y - y0) < layerh);

		for(x = 0; x < basew; ++x) {
			ff_getpixel(basefd, p);
			if(x >= x0 && (x - x0) < layerw && ycheck) {
				ff_getpixel(layerfd, lp);
				overlay(p, lp, p);
			}

			ff_putpixel(outfd, p);
		}

		if(ycheck && xskip) ff_skippixels(layerfd, xskip);
	}
	if(yskip) ff_skippixels(layerfd, yskip);

	return 0;
}
