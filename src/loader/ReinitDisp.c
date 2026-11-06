typedef struct { unsigned int chcr; } sceDmaChan;

extern void sceGsSyncV(int mode);
extern void sceDmaReset(int mode);
extern sceDmaChan *sceDmaGetChan(int id);
extern int sceDmaSync(sceDmaChan *d, int mode, int timeout);
extern int sceGsResetPath(void);
extern void sceGsResetGraph(short mode, short inter, short omode, short ffmode);
extern int sceGsSetDefDBuff(void *db, short psm, short w, short h, short ztest, short zpsm, short clear);
extern void FlushCache(int mode);
extern int sceGsSwapDBuff(void *db, int id);
extern int sceGsSyncPath(int mode, unsigned short timeout);
extern int scePrintf(const char *fmt, ...);

extern char D_0013EB60[];
extern char D_00137C60[];
extern int D_0013A130;
extern int D_0013A134;
extern int D_0013A138;

void ReinitDisp(void) {
    char *db = D_0013EB60;

    sceGsSyncV(0);
    sceDmaReset(1);
    sceDmaSync(sceDmaGetChan(0), 0, 100);
    sceDmaSync(sceDmaGetChan(1), 0, 100);
    sceDmaSync(sceDmaGetChan(2), 0, 100);
    sceDmaGetChan(0)->chcr |= 0x40;
    sceDmaGetChan(1)->chcr |= 0x40;
    sceDmaGetChan(2)->chcr |= 0x40;
    sceGsResetPath();
    sceGsSyncV(0);
    D_0013A130 = 640;
    D_0013A134 = 448;
    sceGsResetGraph(0, 1, 2, 0);
    sceGsSetDefDBuff(db, 0, D_0013A130, D_0013A134, 2, 0, 1);
    sceGsSyncV(0);
    D_0013A138 = 0;
    FlushCache(0);
    sceGsSwapDBuff(db, D_0013A138);
    while (sceGsSyncPath(1, 0)) {
        scePrintf(D_00137C60);
    }
}
