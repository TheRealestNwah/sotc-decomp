extern void AI_UpdateVelocity(float *, float, float);
extern void func_000B9798(char *);

static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static void func_000B9F18(char *o)
{
    int r;
    int k;
    float f = *(float *)(o + 0x1F4);
    float d;

    if (f < 0.0f ? f < -0.7071067f : 0.7071067f < f) {
        r = 0;
    } else {
        d = vecDot((float *)(o + 0x1F0), (float *)(o + 0x130));
        if (d < 0.0f ? d < -0.7071067f : 0.7071067f < d)
            r = 1;
        else
            r = 0;
    }
    f = *(float *)(o + 0x1C8);
    if (r)
        k = 0.0f <= f ? 0x1F : 0x1E;
    else
        k = 0.0f <= f ? 0x1D : 0x1C;
    *(int *)(o + 0x16C) = k;
    if (k == 0x1C)
        *(int *)(o + 0x170) = 0x15;
    else if (k == 0x1D)
        *(int *)(o + 0x170) = 0x16;
    else if (k == 0x1E)
        *(int *)(o + 0x170) = 0x17;
    else if (k == 0x1F)
        *(int *)(o + 0x170) = 0x18;
    func_000B9798(o);
    AI_UpdateVelocity((float *)(o + 0x26C), 0.0f, *(float *)(*(char **)(o + 0x64) + 0x5C));
}
