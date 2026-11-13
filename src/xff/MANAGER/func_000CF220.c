extern unsigned int getVIntrCnt(void);
extern void waitVscheduler(void);
extern void iosDeleteThread(int);
extern float B_0014DBB0;
extern float D_00137708;
extern int D_0013771C;

static void func_000CF220(void)
{
    unsigned int start = getVIntrCnt();
    float elapsed = 0.0f;

    while (elapsed < B_0014DBB0 && !D_0013771C) {
        elapsed = (getVIntrCnt() - start) * 0x1.11111p-6f;
        waitVscheduler();
        D_00137708 = 1.0f - (B_0014DBB0 - elapsed) / B_0014DBB0;
    }
    D_00137708 = 1.0f;
    iosDeleteThread(0);
}
