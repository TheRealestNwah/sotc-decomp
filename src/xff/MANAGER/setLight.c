typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec;

extern Vec B_001486B0, B_001486C0, B_001486D0;
extern Vec B_001486E0, B_001486F0, B_00148700, B_00148710;
extern int B_00148720[4];
extern void iosMakeLightColorMatrix(void *, Vec *, Vec *, Vec *, Vec *);
extern void iosMakeNormalLightMatrix(void *, Vec *, Vec *, Vec *, Vec *);

static inline void vecUnitW(Vec *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
}

static inline void vecNormalize(Vec *dst, Vec *src)
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
                         : : "r"(dst), "r"(src) : "memory");
}

void setLight(void *colorMat, void *normalMat)
{
    Vec dir[3];
    Vec col[4];

    if (B_00148720[0])
        col[0].q = B_001486E0.q;
    else
        vecUnitW(&col[0]);
    if (B_00148720[1])
        col[1].q = B_001486F0.q;
    else
        vecUnitW(&col[1]);
    if (B_00148720[2])
        col[2].q = B_00148700.q;
    else
        vecUnitW(&col[2]);
    if (B_00148720[3])
        col[3].q = B_00148710.q;
    else
        vecUnitW(&col[3]);
    iosMakeLightColorMatrix(colorMat, &col[0], &col[1], &col[2], &col[3]);
    vecNormalize(&dir[0], &B_001486B0);
    vecNormalize(&dir[1], &B_001486C0);
    vecNormalize(&dir[2], &B_001486D0);
    iosMakeNormalLightMatrix(normalMat, &dir[0], &dir[1], &dir[2], &dir[0]);
}
