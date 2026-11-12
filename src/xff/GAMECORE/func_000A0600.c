typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetLayoutClass(int);
extern void *isysGetThisSubThread(void);
extern float AI_GetInterRatioOutCut(float, float, float, float, float);
extern char ZUnitVector[];

static inline void quatRotateVector(Vec4 *out0, float *quat0, char *vec0)
{
    register char *vec __asm__("$4") = vec0;
    register Vec4 *out __asm__("$2") = out0;
    register float *quat __asm__("$3") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

#ifdef NONMATCHING /* 157 diffs (mostly a 3-word shift): early-exit shape and delay slots; also covers the tail at func_000A0850 */
static float func_000A0600(char *a, char *b)
{
    Vec4 v __attribute__((aligned(16)));
    float dist, d, x, r1, r2, r3;
    float one = 1.0f;
    char *thr, *la, *lt;

    if (*(int *)a == 8 && *(int *)b == 5) {
    thr = (char *)isysGetThisSubThread();
    la = GetLayoutClass(*(int *)(a + 0x24));
    lt = GetLayoutClass((int)thr);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dist) : "r"(*(char **)(lt + 0x134)), "r"(b + 0x50) : "$2");
    quatRotateVector(&v, *(float **)(la + 0x13C), ZUnitVector);
    v.f[1] = 0.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&v) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(&v), "r"(a + 0x240) : "$2");
    x = 0.0f;
    if (0.0f < d) {
        float len;
        __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             ".word 0x4BA703BD\n"
                             "vwaitq\n"
                             "cfc2.ni $2, $vi22\n"
                             "mtc1 $2, %0\n"
                             : "=f"(len) : "r"(a + 0x2E0) : "$2");
        x = d * (*(float *)(b + 0x1C) - len);
    }
    r1 = AI_GetInterRatioOutCut(x, 0.0f, 2.0f, 0.0f, 1.0f);
    x = d * dist * *(float *)(a + 0xA0);
    if (x < 0.0f)
        x = 0.0f;
    r2 = AI_GetInterRatioOutCut(x, 1.0f, 10.0f, 0.0f, 3.0f);
    r3 = AI_GetInterRatioOutCut(*(float *)(b + 0x1C), 5.0f, 10.0f, 0.0f, 1.0f);
    one = one + r1 + r2 * r3;
    }
    return one;
}
#endif
