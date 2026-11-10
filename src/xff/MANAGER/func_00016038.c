extern int D_001359F4;
extern char D_00135A00[];
extern void FlushCache(int);
extern int getDispBufferAddressTBP(void);
extern void iosFree(int);
extern void iosGetFontInfo(void *, int);
extern void iosSyncGP(void);
extern void iosTransTex(void *, int, int, int, int);

static void func_00016038(void) {
    int info[8];
    int info2[8];
    int i = 0;
    iosGetFontInfo(info, D_001359F4);
    do {
        FlushCache(0);
        iosSyncGP();
        iosTransTex((char *)(info[2]) + (i << 15), getDispBufferAddressTBP() + ((i % 7) << 10), 0x100, 0x100, (i / 7) ? 0x2C : 0x24);
        i++;
    } while (i < 0xE);
    FlushCache(0);
    iosSyncGP();
    iosTransTex(D_00135A00, 0x3FB8, 8, 2, 0);
    FlushCache(0);
    iosSyncGP();
    iosTransTex(D_00135A00 + 0x40, 0x3FB9, 8, 2, 0);
    FlushCache(0);
    iosSyncGP();
    iosGetFontInfo(info2, *(int *)(D_00135A00 - 0xC));
    if (info2[2] != 0) {
        iosFree(info2[2]);
        info2[2] = 0;
    }
}
