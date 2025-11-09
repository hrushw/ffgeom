#include <stdint.h>

int ff_init(uint32_t, uint32_t, uint8_t[8]);
int ff_rect(uint32_t, uint32_t, uint32_t, uint32_t, uint8_t[8]);
int ff_ellipse(uint32_t, uint32_t, uint32_t, uint32_t, uint8_t[8]);
int ff_blip(uint32_t width, uint32_t height, uint8_t[4][8]);
