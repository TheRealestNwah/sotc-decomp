typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
#define VU_OUTER_PRODUCT(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vopmula.xyz ACC, vf05, vf06\n" \
                         "vopmsub.xyz vf07, vf06, vf05\n" \
                         "vsub.w vf07, vf07, vf07\n" \
                         "sqc2 vf07, 0x0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")
extern Vec4 YUnitVector;
extern Vec4 ZUnitVector;
extern Vec4 ZUnitVectorInv;

void iosGetArbitraryUpVectorElement(float *out, float *v)
{
    Vec4 t;
    float *axis;
    if (v[1] > 0.70699996f) axis = ZUnitVectorInv.f;
    else if (v[1] < -0.70699996f) axis = ZUnitVector.f;
    else axis = YUnitVector.f;
    VU_OUTER_PRODUCT(&t, v, axis);
    VU_OUTER_PRODUCT(out, &t, v);
}
