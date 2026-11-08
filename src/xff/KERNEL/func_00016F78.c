extern void iosDebPcVsyncCounterCheck(void);
extern void waitVscheduler(void);
extern void iosPushVu0Registers(void);
extern void iosPopVu0Registers(void);
extern int iosCheckDrawFinish(void);
extern void iosSyncPath(int a, int b);
extern volatile int gpMainCallCounter;
extern void (*D_00040BC4)(void);
extern void (*D_00040BC8)(void);
extern volatile int D_00040BA4;
extern volatile int D_00040BA0;
extern int D_00040BEC;
extern volatile int D_00040BB0;

static void func_00016F78(void)
{
    for (;;) {
        iosDebPcVsyncCounterCheck();
        waitVscheduler();
        iosPushVu0Registers();
        gpMainCallCounter++;
        if (D_00040BC4 != 0) {
            D_00040BC4();
        }
        D_00040BA4 = iosCheckDrawFinish();
        if (D_00040BA4 != 0) {
            if (D_00040BA0 != 0) {
                D_00040BA0 = 0;
                D_00040BEC = D_00040BA0;
            }
            if (D_00040BC8 != 0) {
                D_00040BC8();
            }
            D_00040BB0 = 0;
        } else {
            if (++D_00040BEC > 0x78) {
                iosSyncPath(0, 0);
            }
        }
        iosPopVu0Registers();
    }
}
