typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
#define VU_DOT(ret, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "lqc2 vf06, 0(%2)\n" \
                         "vaddw.x vf07, vf00, vf00w\n" \
                         "vmul.xyz vf06, vf05, vf06\n" \
                         "vaddax.x ACC, vf00, vf06x\n" \
                         "vmadday.x ACC, vf07, vf06y\n" \
                         "vmaddz.x vf06, vf07, vf06z\n" \
                         "qmfc2 $2, vf06\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(a), "r"(b) : "$2")
float iosGetLengthPointToLine(float *out, float *start, float *end, float *point)
{
    Vec4 direction;
    float length, baseDot, pointDot;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vsub.xyzw vf07, vf05, vf06\n"
                         "sqc2 vf07, 0(%0)\n"
                         : : "r"(direction.f), "r"(end), "r"(start) : "memory");
    __asm__ __volatile__("lqc2 vf7, 0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(length) : "r"(direction.f) : "$2");
    VU_DOT(baseDot, start, direction.f);
    VU_DOT(pointDot, point, direction.f);
    baseDot = -baseDot;
    length *= length;
    baseDot += pointDot;
    baseDot /= length;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyzw vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(out), "r"(direction.f), "r"(baseDot) : "memory");
    return baseDot;
}
