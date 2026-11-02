extern void PutString(int attr, const char *format, ...);
extern void PutStringS(int attr, const char *format, ...);
extern int sceSifRebootIop(const char *img);
extern int sceSifSyncIop(void);
extern char D_00136AE8[];
extern char D_0013A018[];
extern char D_0013A020[];
extern char D_0013A028[];

void LoaderSysRebootIop(const char *img) {
    PutString(0xFFFF00, D_00136AE8);
    PutString(0x40FFFF80, D_0013A018, img);
    PutStringS(0xFFFF00, D_0013A020);
    while (sceSifRebootIop(img) == 0) {
    }
    while (sceSifSyncIop() == 0) {
    }
    PutStringS(0xFFFF00, D_0013A028);
}
