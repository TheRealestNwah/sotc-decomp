typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void iosGetRandomVector(Vec4 *);
extern float iosGetRandom(void);

static inline void scaleXYZ(void *out, void *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalizeXYZ(void *out, void *in)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in) : "memory");
}

static void func_000C6450(char *out, Vec4 *dir, float *speed, char *e, int unused, char *p)
{
    Vec4 r;
    Vec4 tmp;
    float s;

    iosGetRandomVector(&r);
    r.f[0] = r.f[0] * *(float *)(p + 0xC) - *(float *)(p + 0xC) * 0.5f;
    r.f[1] = r.f[1] * *(float *)(p + 0xC) - *(float *)(p + 0xC) * 0.5f;
    r.f[2] = r.f[2] * *(float *)(p + 0xC) - *(float *)(p + 0xC) * 0.5f;
    scaleXYZ(&tmp, e + 0x30, *(float *)(p + 0x15C));
    addXYZ(dir, &tmp, &r);
    normalizeXYZ(dir, dir);
    s = *(float *)(p + 0x30) + *(float *)(p + 0x34) * iosGetRandom();
    *speed = s;
    scaleXYZ(out + 0x10, dir, s);
    if (*(float *)(p + 0x40) <= 0.0f)
        scaleXYZ(out + 0x20, dir, *(float *)(p + 0x38));
    else
        ((Vec4 *)(out + 0x20))->q = dir->q;
}
