/*
NAME
	ff_init - print farbfeld image with given dimensions and color to stdout

SYNOPSIS
	ff_init width height color
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ffioutil.h"

void ff_init(
	uint32_t width, uint32_t height,
	uint8_t clr[8]
) {
	ff_magic();

	ff_pn_nbo(width);
	ff_pn_nbo(height);

	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j)
			ff_putpixel(clr);
}


