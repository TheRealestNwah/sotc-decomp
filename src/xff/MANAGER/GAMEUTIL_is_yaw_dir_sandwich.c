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

int GAMEUTIL_is_yaw_dir_sandwich(float *a, float *b, float *c)
{
    Vec4 t1;
    Vec4 t2;
    Vec4 t3;
    VU_OUTER_PRODUCT(&t1, b, a);
    VU_OUTER_PRODUCT(&t2, b, c);
    if (t1.f[1] * t2.f[1] > 0.0f) {
        VU_OUTER_PRODUCT(&t3, a, c);
        if (t2.f[1] * t3.f[1] > 0.0f) return 1;
    }
    return 0;
}
