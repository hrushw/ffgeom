#include <stdint.h>
#include <unistd.h>

#include "ffioutil.h"

uint8_t ff_chtohex(char ch) {
	if('0' <= ch && ch <= '9') return ch - '0';
	if('a' <= ch && ch <= 'f') return ch - 'a' + 10;
	if('A' <= ch && ch <= 'F') return ch - 'A' + 10;
	return 0xFF;
}

int ff_scanclr(char* clr, uint8_t p[8]) {
	uint8_t n;
	for(n = 0; clr[n] && n < 16; ++n) {
		uint8_t hex = ff_chtohex(clr[n]);
		if(hex >= 16) break;
		p[n/2] = (n % 2) ? (p[n/2] * 16) + hex : hex;
	}

	return n < 6 ? 0 : n < 8 ? 6 : n < 12 ? 8 : n < 16 ? 12 : 16;
}

/* Expand color to 32-bit RGBA (sets alpha to 1.0 if not specified) */
void ff_scan2pix(uint8_t clrlen, uint8_t p[8]) {
	p[7] = (p[6] = 0xFF);
	switch(clrlen) {
		case 16:
		case 12:
			return;
		case 8:
			p[7] = (p[6] = p[3]);
			/* fall through */
		case 6:
			p[5] = (p[4] = p[2]);
			p[3] = (p[2] = p[1]);
			p[1] = p[0];
			return;
	}
}

int ff_getclr(char* color, uint8_t p[8]) {
	uint8_t clrlen = ff_scanclr(color, p);
	if(!clrlen) return -1;
	ff_scan2pix(clrlen, p);
	return 0;
}

/* print number in network byte order */
int ff_pn_nbo(uint32_t n) {
	uint8_t nbo[4] = {0};
	nbo[3] = n % 0x100; n /= 0x100;
	nbo[2] = n % 0x100; n /= 0x100;

	nbo[1] = n / 0x100;
	nbo[0] = n % 0x100;

	return (write(1, nbo, 4) != 4) ? -1 : 0;
}

int ff_putpixel(uint8_t clr[8]) {
	return (write(1, clr, 8) != 8) ? -1 : 0;
}


int ff_getpixel(uint8_t clr[8]) {
	return (read(0, clr, 8) != 8) ? -1 : 0;
}

uint32_t ff_scan2sz(uint8_t scan[4]) {
	return (
		(scan[0] * 0x1000000) +
		(scan[1] * 0x0010000) +
		(scan[2] * 0x0000100) +
		(scan[3] * 0x0000001)
	);
}

const char* ffmagic = "farbfeld";
int ff_magic(void) {
	return (write(1, ffmagic, 8) != 8) ? -1 : 0;
}

int ff_chkmagic(void) {
	char magic[8] = {0};
	if( read(0, magic, 8) != 8 ) return -1;
	for(uint8_t i = 0; i < 8; ++i)
		if( magic[i] != ffmagic[i]) return -1;
	return 0;
}

/* Convert pixel bytes to RGBA u16s */
void ff_pixfmt4clr(uint8_t p[8], uint16_t c[4]) {
	for(uint8_t i = 0; i < 4; ++i) c[i] = (p[2*i] * 0x100) + p[2*i + 1];
}

/* Convert RGBA u16s to pixel bytes */
void ff_4clrfmtpix(uint16_t c[4], uint8_t p[8]) {
	for(uint8_t i = 0; i < 4; ++i) p[2*i] = c[i] / 0x100, p[2*i + 1] = c[i] % 0x100;
}

