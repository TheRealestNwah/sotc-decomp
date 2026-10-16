typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
#define VU_SUB_XYZ(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "lqc2 vf06, 0(%2)\n" \
                         "vsub.xyz vf05, vf05, vf06\n" \
                         "sqc2 vf05, 0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")
#define VU_INNER_PRODUCT(ret, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vaddw.x vf07, vf00, vf00w\n" \
                         "vmul.xyz vf06, vf05, vf06\n" \
                         "vaddax.x ACC, vf00, vf06x\n" \
                         "vmadday.x ACC, vf07, vf06y\n" \
                         "vmaddz.x vf06, vf07, vf06z\n" \
                         "qmfc2 $2, vf06\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(a), "r"(b) : "$2")
#define VU_SCALE_XYZ(dst, src, scale) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "qmtc2 %2, vf06\n" \
                         "vmulx.xyz vf05, vf05, vf06x\n" \
                         "sqc2 vf05, 0x0(%0)\n" \
                         : : "r"(dst), "r"(src), "r"(scale) : "memory")

void iosGetExceptAxisVector(float *out, float *v, float *axis)
{
    Vec4 t;
    float d;
    VU_INNER_PRODUCT(d, v, axis);
    VU_SCALE_XYZ(&t, axis, d);
    VU_SUB_XYZ(out, v, &t);
}
