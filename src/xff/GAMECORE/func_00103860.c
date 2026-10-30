typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_00103860(char *o, float *dir, Vec4 *out)
{
    char *c = *(char **)(o + 0xCC);
    Vec4 tmp;

    vecScale(tmp.f, dir, -*(float *)(c + 0x194));
    tmp.f[1] += *(float *)(c + 0x198);
    vecAdd(out->f, (float *)(o + 0x130), tmp.f);
    out->f[3] = 1.0f;
    ((Vec4 *)(c + 0x160))->q = out->q;
}
