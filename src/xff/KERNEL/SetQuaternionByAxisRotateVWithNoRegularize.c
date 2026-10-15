typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern float iosGetTableSin(short);
extern float iosGetTableCos(short);

void SetQuaternionByAxisRotateVWithNoRegularize(Vec4 *q, short a, Vec4 *axis)
{
    short h = a >> 1;
    float s = iosGetTableSin(h);
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyzw vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(q), "r"(axis), "r"(s) : "memory");
    q->f[3] = iosGetTableCos(h);
}
