#ifndef FF_ROUTINES_H
#define FF_ROUTINES_H

#include <stdint.h>

int ff_rect(int, uint32_t, uint32_t, uint8_t[8]);
int ff_blip(int, uint32_t, uint32_t, uint8_t[4][8]);
int ff_overlay(int, int, int, uint32_t, uint32_t);

#endif
