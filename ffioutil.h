#include <stdint.h>

void ff_argchk(int, int, char*);

int ff_scanclr(char*, uint8_t[8]);
void ff_scan2pix(uint8_t, uint8_t[8]);
int ff_getclr(char*, uint8_t[8]);

int ff_getpixel(uint8_t[8]);
uint32_t ff_scan2sz(uint8_t[4]);

int ff_magic(void);
int ff_chkmagic(void);

int ff_pn_nbo(uint32_t);
int ff_putpixel(uint8_t[8]);

void ff_pixfmt4clr(uint8_t[8], uint16_t[4]);
void ff_4clrfmtpix(uint16_t[4], uint8_t[8]);
