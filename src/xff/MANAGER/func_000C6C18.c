typedef int s128 __attribute__((mode(TI)));
/* dst = a * b */
#define VU_MUL_MATRIX(dst, a, b) \
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "lqc2 vf24, 0x0(%2)\n" \
                         "lqc2 vf25, 0x10(%2)\n" \
                         "lqc2 vf26, 0x20(%2)\n" \
                         "lqc2 vf27, 0x30(%2)\n" \
                         "vmulax.xyzw ACC, vf14, vf24x\n" \
                         "vmadday.xyzw ACC, vf15, vf24y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf24z\n" \
                         "vmaddw.xyzw vf24, vf17, vf24w\n" \
                         "vmulax.xyzw ACC, vf14, vf25x\n" \
                         "vmadday.xyzw ACC, vf15, vf25y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf25z\n" \
                         "vmaddw.xyzw vf25, vf17, vf25w\n" \
                         "vmulax.xyzw ACC, vf14, vf26x\n" \
                         "vmadday.xyzw ACC, vf15, vf26y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf26z\n" \
                         "vmaddw.xyzw vf26, vf17, vf26w\n" \
                         "vmulax.xyzw ACC, vf14, vf27x\n" \
                         "vmadday.xyzw ACC, vf15, vf27y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf27z\n" \
                         "vmaddw.xyzw vf27, vf17, vf27w\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf27, 0x30(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")


extern void iosCopyMatrix(void *, void *);
extern void iosRotMatrixFromDirection(float *, float *, float *, int);
extern float ZUnitVector[4];
extern char B_00149A00[];
extern char B_00149A40[];

static void func_000C6C18(void *m, void *src, float *dir, char *d, int mode)
{
    float tmp[16] __attribute__((aligned(16)));
    char *b;

    iosCopyMatrix(m, src);
    if (*(int *)(d + 0x60) == 1) {
        iosRotMatrixFromDirection(tmp, ZUnitVector, dir, 1);
        VU_MUL_MATRIX(m, tmp, m);
    }
    if (mode == 1) {
        if (*(int *)(d + 0x34) == 1)
            b = B_00149A00;
        else if (*(int *)(d + 0x34) == 2)
            b = B_00149A40;
        else
            return;
        VU_MUL_MATRIX(m, b, m);
    }
}
