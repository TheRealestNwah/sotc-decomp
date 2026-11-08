extern void FlushCache(int);
extern void func_00016380(void);
extern void iosCopyFrameBuffer(void);
extern void iosDlSwap(void);
extern void iosDlTrans(void);
extern void iosGsInitDC(void);
extern void iosGsResetCRTC(void);
extern void iosSyncPath(int, int);
extern void iosSyncV(int);
extern int sceGsGetIMR(void);
extern int sceGsPutIMR(int);
extern volatile int D_00040BB0;
extern void (*D_00040BC0)(void);
extern int D_00040BD0;
extern int D_00040BE8;

static inline void swap_buffers(void)
{
    if (D_00040BC0 != 0) {
        D_00040BC0();
    }
    iosGsResetCRTC();
    D_00040BB0 = 1;
    sceGsPutIMR(sceGsGetIMR() & ~0x200);
    iosDlSwap();
    iosDlTrans();
}

void iosSyncGP(void)
{
    FlushCache(0);
    iosGsInitDC();
    if (D_00040BE8 != 0) {
        D_00040BE8 = 0;
        swap_buffers();
    } else {
        iosCopyFrameBuffer();
        swap_buffers();
        if (D_00040BD0 != 0) {
            func_00016380();
        }
    }
    FlushCache(0);
    swap_buffers();
    iosSyncPath(0, 0);
    iosSyncV(1);
}
