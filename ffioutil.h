int ff_scanclr(char*, uint8_t[8]);
void ff_scan2pix(uint8_t, uint8_t[8]);
void ff_getclr_die(char*, uint8_t[8]);

int ff_getpixel(uint8_t[8]);
uint32_t ff_scan2sz(uint8_t[4]);
void ff_getpixel_die(uint8_t[8]);

void ff_magic(void);
int ff_chkmagic(void);

void ff_pn_nbo(uint32_t);
void ff_putpixel(uint8_t[8]);

