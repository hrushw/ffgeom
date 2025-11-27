#include <stdint.h>
#include "ffioutil.h"

int ff_rect (
	int fd,
	uint32_t width, uint32_t height,
	uint8_t clr[8]
) {
	uint32_t y, x;

	ff_header_init(fd, width, height);
	for(y = 0; y < height; ++y)
		for(x = 0; x < width; ++x)
			ff_putpixel(fd, clr);

	return 0;
}
