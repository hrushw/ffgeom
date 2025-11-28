#ifndef FF_IOUTIL_H
#define FF_IOUTIL_H

#include <stdint.h>

struct u128 {
	uint64_t low;
	uint64_t high;
};

void ff_argchk(int, int, char*);

int ff_scanclr(char*, uint8_t[8]);
void ff_scan2pix(uint8_t, uint8_t[8]);
int ff_getclr(char*, uint8_t[8]);

uint32_t ff_scan2sz(uint8_t[4]);
int ff_pn_nbo(int, uint32_t);

int ff_magic(int);
int ff_chkmagic(int);

int ff_getpixel(int, uint8_t[8]);
int ff_putpixel(int, uint8_t[8]);
int ff_skippixels(int, uint64_t);

void ff_pixfmt4clr(uint8_t[8], uint16_t[4]);
void ff_4clrfmtpix(uint16_t[4], uint8_t[8]);

void ff_header_init(int, uint32_t, uint32_t);
void ff_getsz(int, uint32_t*, uint32_t*);

#endif
