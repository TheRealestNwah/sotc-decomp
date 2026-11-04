typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 YUnitVector;
extern Vec4 YUnitVectorInv;
extern void iosGetReflectVector(void *, void *, Vec4 *);

static inline void scaleXYZ(void *out, void *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static void func_000C68E0(char *e, char *x, char *y, char *p)
{
    float d = *(float *)(y + 0x134) * *(float *)(e + 0x4C);
    float lo = *(float *)(x + 0x150) - d;
    float hi = *(float *)(x + 0x154) + d;

    if (lo <= *(float *)(e + 0x4)) {
        *(float *)(e + 0x4) = lo;
        iosGetReflectVector(e + 0x10, e + 0x10, &YUnitVectorInv);
        iosGetReflectVector(e + 0x20, e + 0x20, &YUnitVectorInv);
        scaleXYZ(e + 0x10, e + 0x10, *(float *)(p + 0x130));
        scaleXYZ(e + 0x20, e + 0x20, *(float *)(p + 0x134));
        *(float *)(e + 0x54) *= *(float *)(p + 0x138);
    }
    if (*(float *)(e + 0x4) <= hi) {
        *(float *)(e + 0x4) = hi;
        iosGetReflectVector(e + 0x10, e + 0x10, &YUnitVector);
        iosGetReflectVector(e + 0x20, e + 0x20, &YUnitVector);
        scaleXYZ(e + 0x10, e + 0x10, *(float *)(p + 0x13C));
        scaleXYZ(e + 0x20, e + 0x20, *(float *)(p + 0x140));
        *(float *)(e + 0x54) *= *(float *)(p + 0x144);
    }
}
