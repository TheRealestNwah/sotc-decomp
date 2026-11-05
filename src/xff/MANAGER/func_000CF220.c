extern int getVIntrCnt(void);
extern void iosDeleteThread(int);
extern void waitVscheduler();
extern float B_0014DBB0;
extern float D_00137708;
extern int D_0013771C;

static void func_000CF220(void)
{
    int start = getVIntrCnt();
    float t = 0.0f;

    if (t < B_0014DBB0) {
        while (D_0013771C == 0) {
            unsigned int n = getVIntrCnt() - start;
            t = (float)n * 0.016666666f;
            waitVscheduler();
            D_00137708 = 1.0f - (B_0014DBB0 - t) / B_0014DBB0;
            if (!(t < B_0014DBB0))
                break;
        }
    }
    D_00137708 = 1.0f;
    iosDeleteThread(0);
}
