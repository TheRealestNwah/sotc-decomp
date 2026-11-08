extern int D_00040BE8;
extern void (*D_00040BC0)(void);
extern volatile int D_00040BB0;
extern int D_00040BD0;
extern void iosGsInitDC(void);
extern void iosGsResetCRTC(void);
extern int sceGsGetIMR(void);
extern int sceGsPutIMR(int imr);
extern void iosDlSwap(void);
extern void iosDlTrans(void);
extern void iosCopyFrameBuffer(void);
extern void func_00016380(void);

void iosGPFrameInit(void)
{
    iosGsInitDC();
    if (D_00040BE8) {
        void (*fn)(void) = D_00040BC0;
        D_00040BE8 = 0;
        if (fn) {
            fn();
        }
        iosGsResetCRTC();
        D_00040BB0 = 1;
        sceGsPutIMR(sceGsGetIMR() & ~0x200);
        iosDlSwap();
        iosDlTrans();
    } else {
        iosCopyFrameBuffer();
        if (D_00040BC0) {
            D_00040BC0();
        }
        iosGsResetCRTC();
        D_00040BB0 = 1;
        sceGsPutIMR(sceGsGetIMR() & ~0x200);
        iosDlSwap();
        iosDlTrans();
        if (D_00040BD0) {
            func_00016380();
            __asm__ volatile(""); /* the original does not tail-call here */
        }
    }
}
