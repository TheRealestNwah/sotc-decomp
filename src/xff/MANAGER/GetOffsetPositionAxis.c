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

void GetOffsetPositionAxis(float *out, float *base, s128 *offs, float *ax, float *ay, float *az)
{
    Vec4 o;
    Vec4 t;
    o.q = *offs;
    VU_SCALE_XYZ(&t, ax, o.f[0]);
    VU_ADD_XYZ(out, base, &t);
    VU_SCALE_XYZ(&t, ay, o.f[1]);
    VU_ADD_XYZ(out, out, &t);
    VU_SCALE_XYZ(&t, az, o.f[2]);
    VU_ADD_XYZ(out, out, &t);
}
