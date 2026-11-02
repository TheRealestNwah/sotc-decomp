typedef struct {
    float m[4][4];
} __attribute__((aligned(16))) Matrix;

extern int B_001482A0;
extern Matrix B_00147AA0[];
extern void *memset(void *, int, unsigned int);
extern void iosGetSinCosf(float *, float);

static inline void mulCurrentMatrix(Matrix *r)
{
    Matrix *m = &B_00147AA0[B_001482A0];

    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf14, 0x0(%0)\n"
                         "lqc2 vf15, 0x10(%0)\n"
                         "lqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf17, 0x30(%0)\n"
                         "lqc2 vf24, 0x0(%1)\n"
                         "lqc2 vf25, 0x10(%1)\n"
                         "lqc2 vf26, 0x20(%1)\n"
                         "lqc2 vf27, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         ".set reorder\n"
                         : : "r"(m), "r"(r) : "memory");
}

static inline Matrix rotationx(float *sc)
{
    Matrix r;

    memset(r.m[0], 0, sizeof(r.m[0]));
    r.m[0][0] = 1.0f;
    r.m[1][0] = 0.0f;
    r.m[1][1] = sc[0];
    r.m[1][2] = sc[1];
    r.m[1][3] = 0.0f;
    r.m[2][0] = 0.0f;
    r.m[2][1] = -sc[1];
    r.m[2][2] = sc[0];
    r.m[2][3] = 0.0f;
    memset(r.m[3], 0, sizeof(r.m[3]));
    r.m[3][3] = 1.0f;
    return r;
}

#ifdef NONMATCHING
void glRotatex(float angle)
{
    float sc[2];
    Matrix r;
    iosGetSinCosf(sc, angle);
    r = rotationx(sc);
    mulCurrentMatrix(&r);
}
#endif
