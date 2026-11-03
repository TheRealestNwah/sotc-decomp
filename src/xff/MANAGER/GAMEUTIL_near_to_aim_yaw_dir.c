#ifdef NONMATCHING /* 21 instruction diffs: target uses branch-likely for the *rot store and a different v0/v1 allocation for the sandwich vectors */
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

extern int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(void *, float *, float, float *);

static inline int is_yaw_dir_sandwich(float *a, float *b, float *c)
{
    Vec4 t1;
    Vec4 t2;
    Vec4 t3;
    int r;
    VU_OUTER_PRODUCT(&t1, b, a);
    VU_OUTER_PRODUCT(&t2, b, c);
    r = 0;
    if (t1.f[1] * t2.f[1] > 0.0f) {
        VU_OUTER_PRODUCT(&t3, a, c);
        r = t2.f[1] * t3.f[1] > 0.0f;
    }
    return r;
}

int GAMEUTIL_near_to_aim_yaw_dir(Vec4 *out, int *rot, Vec4 *cur, float speed, Vec4 *aim)
{
    Vec4 v;
    int r;

    v.q = cur->q;
    r = GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(out, v.f, speed, aim->f);
    if (rot != 0) {
        *rot = r;
    }
    if (is_yaw_dir_sandwich(aim->f, v.f, out->f) != 1) {
        return 0;
    }
    if (out != 0) {
        out->q = aim->q;
    }
    return 1;
}
#endif
