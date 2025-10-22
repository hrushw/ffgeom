#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

void ff_getclr_die(char* color, uint8_t p[8]) {
	uint8_t clrlen = ff_scanclr(color, p);
	if(!clrlen)
		fprintf(stderr, "Error: invalid color\n"), exit(EXIT_FAILURE);
	ff_scan2pix(clrlen, p);
}



/* print number in network byte order */
void ff_pn_nbo(uint32_t n) {
	uint8_t b0 = n % 256; n /= 256;
	uint8_t b1 = n % 256; n /= 256;

	putchar(n / 256);
	putchar(n % 256);
	putchar(b1);
	putchar(b0);
}

void ff_putpixel(uint8_t clr[8]) {
	for(uint8_t i = 0; i < 8; ++i) putchar(clr[i]);
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

void ff_getpixel_die(uint8_t p[8]) {
	if(ff_getpixel(p))
		fprintf(stderr, "ERROR: Early EOF!\n"), exit(EXIT_FAILURE);
}



void ff_magic(void) {
	putchar('f');
	putchar('a');
	putchar('r');
	putchar('b');
	putchar('f');
	putchar('e');
	putchar('l');
	putchar('d');
}

int ff_chkmagic(void) {
	if(getchar() != 'f') return -1;
	if(getchar() != 'a') return -1;
	if(getchar() != 'r') return -1;
	if(getchar() != 'b') return -1;
	if(getchar() != 'f') return -1;
	if(getchar() != 'e') return -1;
	if(getchar() != 'l') return -1;
	if(getchar() != 'd') return -1;
	return 0;
}

