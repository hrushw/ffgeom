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

int ff_init(int argc, char* argv[]) {
	ff_argchk(argc, 3, "Usage: ff_init width height color\n");
	uint32_t width = strtol(argv[0], NULL, 0);
	uint32_t height = strtol(argv[1], NULL, 0);
	uint8_t clr[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF };
	ff_getclr_die(argv[2], clr);

	/* start printing, beginning with magic value */
	ff_magic();
	ff_pn_nbo(width);
	ff_pn_nbo(height);
	for(uint32_t i = 0; i < height; ++i)
		for(uint32_t j = 0; j < width; ++j)
			ff_putpixel(clr);

	exit(EXIT_SUCCESS);
}


