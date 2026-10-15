extern void (*D_00040BC0)(void);
extern int D_00040BB0;
extern void iosGsResetCRTC(void);
extern int sceGsGetIMR(void);
extern int sceGsPutIMR(int imr);
extern void iosDlSwap(void);
extern void iosDlTrans(void);

void iosTransGP(void)
{
    volatile int *p;

    if (D_00040BC0 != 0) {
        D_00040BC0();
    }
    iosGsResetCRTC();
    p = &D_00040BB0;
    *p = 1;
    sceGsPutIMR(sceGsGetIMR() & ~0x200);
    iosDlSwap();
    iosDlTrans();
}
