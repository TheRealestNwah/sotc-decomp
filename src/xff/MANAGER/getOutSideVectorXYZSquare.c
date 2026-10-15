typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

float getOutSideVectorXYZSquare(char *p)
{
    Vec4 v;
    float m = *(float *)(p + 0x30);
    float r;
    if (m < *(float *)(p + 0x34))
        m = *(float *)(p + 0x34);
    if (m < *(float *)(p + 0x38))
        m = *(float *)(p + 0x38);
    v.f[0] = m;
    v.f[1] = m;
    v.f[2] = m;
    __asm__ __volatile__("lqc2 vf07, 0(%1)\n"
                         "vmul.xyz vf07, vf07, vf07\n"
                         "vaddy.x vf07, vf07, vf07y\n"
                         "vaddz.x vf07, vf07, vf07z\n"
                         "qmfc2 %0, vf07\n"
                         : "=r"(r) : "r"(&v));
    return r;
}
