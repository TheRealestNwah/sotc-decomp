typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
#define VU_ADD_XYZ(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "lqc2 vf06, 0(%2)\n" \
                         "vadd.xyz vf05, vf05, vf06\n" \
                         "sqc2 vf05, 0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")
#define VU_PLANE_DISTANCE(ret, plane, p) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vaddw.x vf07, vf00, vf00w\n" \
                         "vmul.xyz vf06, vf05, vf06\n" \
                         "vaddax.x ACC, vf00, vf06x\n" \
                         "vmadday.x ACC, vf07, vf06y\n" \
                         "vmaddz.x vf06, vf07, vf06z\n" \
                         "vaddw.x vf06, vf06, vf05w\n" \
                         "qmfc2 $2, vf06\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(plane), "r"(p) : "$2")
#define VU_SCALE_XYZ(dst, src, scale) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "qmtc2 %2, vf06\n" \
                         "vmulx.xyz vf05, vf05, vf06x\n" \
                         "sqc2 vf05, 0x0(%0)\n" \
                         : : "r"(dst), "r"(src), "r"(scale) : "memory")
#define VU_SQUARE_LENGTH(ret, v) \
    __asm__ __volatile__("lqc2 vf07, 0x0(%1)\n" \
                         "vmul.xyz vf07, vf07, vf07\n" \
                         "vaddy.x vf07, vf07, vf07y\n" \
                         "vaddz.x vf07, vf07, vf07z\n" \
                         "qmfc2 $2, vf07\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(v) : "$2")

void GetPlaneFittingPointForUnnormalizedPlane(float *out, float *plane, float *p)
{
    Vec4 t;
    float d;
    float l;
    VU_PLANE_DISTANCE(d, plane, p);
    VU_SQUARE_LENGTH(l, plane);
    VU_SCALE_XYZ(&t, plane, -(d / l));
    VU_ADD_XYZ(out, p, &t);
}
