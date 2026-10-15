typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void iosGetSinCosf(float *, float);

void SetQuaternionByAxisRotateVWithNoRegularizeRadian(Vec4 *q, Vec4 *axis, float a)
{
    float sc[2];
    iosGetSinCosf(sc, a * 0.5f);
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyzw vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(q), "r"(axis), "r"(sc[1]) : "memory");
    q->f[3] = sc[0];
}
