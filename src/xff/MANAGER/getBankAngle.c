typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern float iosGetATan2fExact(float, float);

float getBankAngle(char *c, float *v)
{
    Vec4 r;
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf08x\n"
                         "vmadday.xyzw ACC, vf15, vf08y\n"
                         "vmaddaz.xyzw ACC, vf16, vf08z\n"
                         "vmaddw.xyzw vf10, vf17, vf08w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(&r), "r"(c + 0x1A0), "r"(v) : "memory");
    return iosGetATan2fExact(r.f[1], r.f[0]) - 1.5707963f;
}
