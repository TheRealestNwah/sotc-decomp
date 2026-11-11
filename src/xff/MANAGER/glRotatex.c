typedef struct {
    float m[16];
} __attribute__((aligned(16))) Matrix;

extern int B_001482A0;
extern Matrix B_00147AA0[];
extern void *memset(void *, int, unsigned int);
extern void iosGetSinCosf(float *out, float angle);

static inline void mulCurrentMatrix(Matrix *src)
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
                         : : "r"(m), "r"(src) : "memory");
}

#ifdef NONMATCHING
/* 7 diffs: rotation matrix stores scheduled in a different order (this store order is the best of 150 random orders). Permuter (4 workers, 25 min) only improved it by moving the m[5] store after the matrix is used, which changes behaviour. */
void glRotatex(float angle)
{
    float sc[4];
    Matrix tmp;
    Matrix rot;

    iosGetSinCosf(sc, angle);
    memset(&rot.m[0], 0, 0x10);
    rot.m[5] = sc[0];
    rot.m[10] = sc[0];
    rot.m[4] = 0.0f;
    rot.m[8] = 0.0f;
    rot.m[7] = 0.0f;
    rot.m[0] = 1.0f;
    rot.m[9] = -sc[1];
    rot.m[6] = sc[1];
    rot.m[11] = 0.0f;
    memset(&rot.m[12], 0, 0x10);
    rot.m[15] = 1.0f;
    tmp = rot;
    mulCurrentMatrix(&tmp);
}
#endif
