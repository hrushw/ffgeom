#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "ffioutil.h"

void ff_argchk(int argc, int req, char* usage) {
	if(argc < req) {
		fprintf(stderr, usage);
		exit(EXIT_FAILURE);
	}
}

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

/* assumes p was initialized to 0x000000000000FFFF before scan */
void ff_scan2pix(uint8_t clrlen, uint8_t p[8]) {
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

int ff_getclr_log(char* color, uint8_t p[8]) {
	int ret = 0;
	if((ret = ff_getclr(color, p)))
		fprintf(stderr, "Error: invalid color\n");
	return ret;
}

void ff_getclr_die(char* color, uint8_t p[8]) {
	if(ff_getclr_log(color, p)) exit(EXIT_FAILURE);
}


/* print number in network byte order */
void ff_pn_nbo(uint32_t n) {
	uint8_t nbo[4] = {0};
	nbo[3] = n % 0x100; n /= 0x100;
	nbo[2] = n % 0x100; n /= 0x100;

	nbo[1] = n / 0x100;
	nbo[0] = n % 0x100;

	write(1, nbo, 4);
}

void ff_putpixel(uint8_t clr[8]) {
	if( (write(1, clr, 8) != 8)) exit(EXIT_FAILURE);
}



int ff_getpixel(uint8_t clr[8]) {
	int ch = 0;
	for(uint8_t i = 0; i < 8; ++i) {
		if((ch = getchar()) == EOF) return -1;
		clr[i] = ch;
	}
	return 0;
}

uint32_t ff_scan2sz(uint8_t scan[4]) {
	return (
		scan[0] * 0x1000000 +
		scan[1] * 0x10000 +
		scan[2] * 0x100 +
		scan[3]
	);
}

int ff_getpixel_log(uint8_t p[8]) {
	int ret = 0;
	if((ret =ff_getpixel(p)))
		fprintf(stderr, "ERROR: Early EOF!\n");
	return ret;
}

void ff_getpixel_die(uint8_t p[8]) {
	if(ff_getpixel_log(p)) exit(EXIT_FAILURE);
}

const char* ffmagic = "farbfeld";
void ff_magic(void) {
	if( (write(1, ffmagic, 8) != 8)) exit(EXIT_FAILURE);
}

int ff_chkmagic(void) {
	char magic[8] = {0};
	if( read(0, magic, 8) != 8 ) return -1;
	for(uint8_t i = 0; i < 8; ++i)
		if( magic[i] != ffmagic[i]) return -1;
	return 0;
}

int ff_chkmagic_log(void) {
	int ret = 0;
	if((ret = ff_chkmagic()))
		fprintf(stderr, "ERROR: farbfeld magic value not present! The image may be corrupted.\n");
	return ret;
}

void ff_chkmagic_die(void) {
	if(ff_chkmagic_log()) exit(EXIT_FAILURE);
}

void ff_pixfmt4clr(uint8_t p[8], uint16_t c[4]) {
	for(uint8_t i = 0; i < 4; ++i) c[i] = (p[2*i] * 0x100) + p[2*i + 1];
}

void ff_4clrfmtpix(uint16_t c[4], uint8_t p[8]) {
	for(uint8_t i = 0; i < 4; ++i) p[2*i] = c[i] / 0x100, p[2*i + 1] = c[i] % 0x100;
}
