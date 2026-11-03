#ifdef NONMATCHING /* stack layout differs: 0xC0 frame vs target 0x70 temp-then-copy */
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

typedef struct {
    float x, y, z, w;
} Vec4f __attribute__((aligned(8)));

static inline Vec4f to_pitch_plane(float *v)
{
    Vec4f r;
    r.x = v[1];
    r.y = 0.0f;
    r.z = v[2];
    r.w = 0.0f;
    return r;
}

static inline int is_dir_sandwich(Vec4f *pa, Vec4f *pb, Vec4f *pc)
{
    Vec4 t1;
    Vec4 t2;
    Vec4 t3;
    VU_OUTER_PRODUCT(&t1, pb, pa);
    VU_OUTER_PRODUCT(&t2, pb, pc);
    if (t1.f[1] * t2.f[1] > 0.0f) {
        VU_OUTER_PRODUCT(&t3, pa, pc);
        if (t2.f[1] * t3.f[1] > 0.0f) return 1;
    }
    return 0;
}

int GAMEUTIL_is_reach_aim_pitch_dir(s128 *out, float *cur, float *next, float *aim)
{
    Vec4f a, b, c;

    a = to_pitch_plane(aim);
    b = to_pitch_plane(cur);
    c = to_pitch_plane(next);
    if (is_dir_sandwich(&a, &b, &c) == 1) {
        if (out) *out = *(s128 *)aim;
        return 1;
    }
    if (out) *out = *(s128 *)next;
    return 0;
}
#endif
