extern void PutString(int attr, const char *format, ...);
extern void PutStringS(int attr, const char *format, ...);
extern void sceSifInitRpc(unsigned int mode);
extern int sceSifInitIopHeap(void);
extern int sceSifRebootIop(const char *img);
extern int sceSifSyncIop(void);
extern void sceSifLoadFileReset(void);
extern int sceFsReset(void);
extern int sceCdInit(int mode);
extern int sceCdMmode(int media);
extern void PreparePowerOff(void);
extern int sceDmaReset(int mode);
extern int sceDbcInit(void);
extern void padsysInit(void);
extern int sceSifLoadModule(const char *path, int argsLen, const char *args);
extern void setNewIopIdentifier(const char *name);
extern int usbSerialSysInit(void);
extern char D_00136AE8[];
extern char D_00136B00[];
extern char D_00136B10[];
extern char D_00136B98[];
extern char D_00136BB8[];
extern char D_00136BC8[];
extern char D_00136BD8[];
extern char D_00136BF8[];
extern char D_00136C10[];
extern char D_00136C30[];
extern char D_00136C50[];
extern char D_00136C70[];
extern char D_00136C90[];
extern char D_00136CB0[];
extern char D_0013A018[];
extern char D_0013A020[];
extern char D_0013A028[];
extern char D_0013A038[];
extern char D_0013A040[];
extern char D_0013A048[];
extern char D_0013A050[];
extern char D_0013A058[];
extern char D_0013A060[];
extern char D_0013A068[];
extern char D_0013A070[];

static inline void LoaderSysRebootIop(const char *img) {
    PutString(0xFFFF00, D_00136AE8);
    PutString(0x40FFFF80, D_0013A018, img);
    PutStringS(0xFFFF00, D_0013A020);
    while (sceSifRebootIop(img) == 0) {
    }
    while (sceSifSyncIop() == 0) {
    }
    PutStringS(0xFFFF00, D_0013A028);
}

static inline int LoaderSysLoadIopModule(const char *path, int argsLen, const char *args) {
    int ret;

    PutString(0x4080FF00, D_00136B00);
    PutString(0x80C0FF00, D_0013A018, path);
    PutStringS(0x4080FF00, D_0013A020);
    ret = sceSifLoadModule(path, argsLen, args);
    if (ret < 0) {
        PutStringS(0xFF804000, D_00136B10, path, ret);
        return -1;
    }
    PutStringS(0x4080FF00, D_0013A028);
    return 0;
}

#define LOAD(path, id)                                  \
    if (LoaderSysLoadIopModule(path, 0, 0) < 0) {       \
        while (1) {                                     \
            __asm__ volatile("nop");                    \
            __asm__ volatile("nop");                    \
            __asm__ volatile("nop");                    \
            __asm__ volatile("nop");                    \
            __asm__ volatile("nop");                    \
        }                                               \
    }                                                   \
    setNewIopIdentifier(id)

int func_001033B0(void) {
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    PutString(0xFFFFFF00, D_00136B98);
    PutString(0x80FFC000, D_0013A038, D_00136BB8, D_00136BC8);
    PutStringS(0xFFFFFF00, D_0013A040);
    PutStringS(0x80C0FF00, D_00136BD8);
    sceCdInit(0);
    sceCdMmode(2);
    PutStringS(0x80C0FF00, D_0013A028);
    LoaderSysRebootIop(D_00136BF8);
    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceFsReset();
    sceCdInit(0);
    sceCdMmode(2);
    PreparePowerOff();
    sceSifLoadFileReset();
    sceFsReset();
    sceDmaReset(1);
    LOAD(D_00136C10, D_0013A048);
    LOAD(D_00136C30, D_0013A050);
    LOAD(D_00136C50, D_0013A058);
    LOAD(D_00136C70, D_0013A060);
    sceSifLoadFileReset();
    sceFsReset();
    sceDmaReset(1);
    sceDbcInit();
    padsysInit();
    LOAD(D_00136C90, D_0013A068);
    LOAD(D_00136CB0, D_0013A070);
    return usbSerialSysInit();
}
