#ifdef NONMATCHING /* 63 diffs: the target builds each vector in a temporary and copies it (ld/sd) before loading the next input; this hoists all loads */
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

int GAMEUTIL_is_pitch_dir_sandwich(float *pa, float *pb, float *pc)
{
    Vec4 a;
    Vec4 b;
    Vec4 c;
    Vec4 t1;
    Vec4 t2;
    Vec4 t3;
    a.f[0] = pa[1]; a.i[1] = 0; a.f[2] = pa[2]; a.i[3] = 0;
    b.f[0] = pb[1]; b.i[1] = 0; b.f[2] = pb[2]; b.i[3] = 0;
    c.f[0] = pc[1]; c.i[1] = 0; c.f[2] = pc[2]; c.i[3] = 0;
    VU_OUTER_PRODUCT(&t1, &b, &a);
    VU_OUTER_PRODUCT(&t2, &b, &c);
    if (t1.f[1] * t2.f[1] > 0.0f) {
        VU_OUTER_PRODUCT(&t3, &a, &c);
        if (t2.f[1] * t3.f[1] > 0.0f) return 1;
    }
    return 0;
}
#endif
