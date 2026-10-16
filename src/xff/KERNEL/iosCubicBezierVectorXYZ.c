typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
#define VU_ADD_XYZ(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "lqc2 vf06, 0(%2)\n" \
                         "vadd.xyz vf05, vf05, vf06\n" \
                         "sqc2 vf05, 0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")
#define VU_SCALE_XYZ(dst, src, scale) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "qmtc2 %2, vf06\n" \
                         "vmulx.xyz vf05, vf05, vf06x\n" \
                         "sqc2 vf05, 0x0(%0)\n" \
                         : : "r"(dst), "r"(src), "r"(scale) : "memory")

void iosCubicBezierVectorXYZ(float *out, char *p, float t)
{
    Vec4 tmp;
    float u = 1.0f - t;
    VU_SCALE_XYZ(out, p, u * u);
    VU_SCALE_XYZ(&tmp, p + 0x10, (u + u) * t);
    VU_ADD_XYZ(out, out, &tmp);
    VU_SCALE_XYZ(&tmp, p + 0x20, t * t);
    VU_ADD_XYZ(out, out, &tmp);
}
