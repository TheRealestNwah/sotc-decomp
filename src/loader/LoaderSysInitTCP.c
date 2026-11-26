/* Parked attempt: 1 word differs (+0xB8). The Original fills the bnez delay slot
 with the a1 = mode move stolen from the second func_00104668 call; gcc
 2.96 here picks bnezl. Fall-through clobbers, join barriers and branch
 shapes did not change it. */
#ifdef NONMATCHING
extern void PutString(int attr, const char *format, ...);
extern void PutStringS(int attr, const char *format, ...);
extern int printf(const char *format, ...);
extern int func_00104818(void);
extern void func_00104090(int mode);
extern int func_00104668(int a, int mode);
extern int sceSifMInitRpc(int mode);
extern int sceLibnetInitialize(void *cd, int a, int b, int c);
extern int sceLibnetRegisterHandler(void *cd, void *buf);
extern int sceInetAddress2String(void *cd, void *buf, char *name, int len, void *addr);
extern int sceInetAddress2Name(void *cd, void *buf, int flags, char *name, int len, void *addr, int ms, int nretry);
extern int LoaderSysLoadIopModule(const char *path, int argsLen, const char *args);
extern int LoaderSysUnloadIopModuleByName(const char *name, int a, int b, int c);
extern int D_0013A0EC;
extern char D_0013D000[];
extern char D_00131FC0[];
extern char D_00137258[], D_00137270[], D_00137290[], D_001372B0[], D_001372D8[];
extern char D_001372E8[], D_00137300[], D_00137328[], D_00137340[], D_00137360[];
extern char D_00137380[], D_001373B8[], D_001373C8[];
extern char D_0013A0F0[], D_0013A0F8[], D_0013A100[], D_0013A108[], D_0013A110[];

#define HANG()                       \
    while (1) {                      \
        __asm__ volatile("nop");     \
        __asm__ volatile("nop");     \
        __asm__ volatile("nop");     \
        __asm__ volatile("nop");     \
        __asm__ volatile("nop");     \
    }

void *LoaderSysInitTCP(void)
{
    char name[0x80];
    char addr[0x80];
    int mode;

    if (D_0013A0EC) {
        return D_0013D000;
    }
    mode = func_00104818();
    func_00104090(mode);
    sceSifMInitRpc(0);
    sceLibnetInitialize(D_0013D000, 0x800, 0x2000, 0x20);
    if (sceLibnetRegisterHandler(D_0013D000, D_0013D000 + 0x40) < 0) {
        printf(D_00137258);
        HANG();
    }
    LoaderSysLoadIopModule(D_00137270, 0, 0);
    LoaderSysLoadIopModule(D_00137290, 0, 0);
    PutString(-0x100, D_001372B0);
    if (mode == 0) {
        if (func_00104668(1, 0)) {
            goto connected;
        }
        PutStringS(0xFF804000, D_001372D8);
        PutString(-0x100, D_001372E8);
        mode = 3;
    }
    if (!func_00104668(0, mode)) {
        PutStringS(0xFF804000, D_001372D8);
        PutString(-0x100, D_00137300);
    }
connected:
    if (sceInetAddress2String(D_0013D000, D_0013D000 + 0x40, addr, 0x80, D_00131FC0)) {
        printf(D_00137328);
        HANG();
    }
    if (sceInetAddress2Name(D_0013D000, D_0013D000 + 0x40, 0, name, 0x80, D_00131FC0, 0, 0)) {
        name[0] = 0;
        printf(D_00137340, addr);
    } else {
        printf(D_00137360, name, addr);
    }
    PutString(-0x100, D_0013A0F0);
    LoaderSysUnloadIopModuleByName(D_0013A0F8, 0, 0, 0);
    LoaderSysUnloadIopModuleByName(D_0013A100, 0, 0, 0);
    PutString(-0x100, D_0013A108);
    PutString(0xFFFF00, D_00137380);
    if (name[0]) {
        PutString(0xFFFF00, D_001373B8);
        PutString(0x40FF8000, D_0013A110, name);
    }
    PutString(0xFFFF00, D_001373C8);
    PutString(0x40FF8000, D_0013A110, addr);
    PutString(0xFFFF00, D_00137380);
    PutStringS(0xFFFF00, D_0013A108);
    D_0013A0EC = 1;
    return D_0013D000;
}
#endif
