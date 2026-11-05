extern char gcGlobalVar[];
extern long __muldi3(long, long);

static inline void setRatio(float ratio)
{
    char *g = gcGlobalVar;

    *(float *)(g + 0x1A0) = ratio;
    *(unsigned long *)(g + 0x160) = *(unsigned long *)(g + 0x148) + *(unsigned long *)(g + 0x160);
    *(unsigned long *)(g + 0x158) = ((*(unsigned long *)g << 8 >> 8) * (int)(ratio * 256.0f)) >> 8;
    *(unsigned long *)(g + 0x148) = 0;
}

static void func_0000BA70(void)
{
    char *g = gcGlobalVar;
    float target = *(float *)(g + 0x1A8);
    float old = *(float *)(g + 0x1A0);
    float d = target - old;
    float cur;
    float vel = *(float *)(g + 0x1A4);

    if (d == 0.0f) {
        *(float *)(g + 0x1A4) = 0.0f;
        return;
    }
    cur = old + vel * *(float *)(g + 0x180);
    if (d > 0.0f) {
        if (vel <= 0.0f || target < cur)
            cur = target;
    } else {
        if (vel >= 0.0f || cur < target)
            cur = target;
    }
    setRatio(cur);
}
