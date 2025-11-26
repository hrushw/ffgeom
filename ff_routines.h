#ifndef FF_ROUTINES_H
#define FF_ROUTINES_H

#include <stdint.h>

int ff_init(uint32_t, uint32_t, uint8_t[8]);
int ff_blip(uint32_t width, uint32_t height, uint8_t[4][8]);

#endif
