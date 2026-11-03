#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
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

static inline int is_yaw_dir_sandwich(float *a, float *b, float *c)
{
    Vec4 t1;
    Vec4 t2;
    Vec4 t3;
    int r;
    VU_OUTER_PRODUCT(&t1, b, a);
    VU_OUTER_PRODUCT(&t2, b, c);
    if (t1.f[1] * t2.f[1] > 0.0f) {
        VU_OUTER_PRODUCT(&t3, a, c);
        r = t2.f[1] * t3.f[1] > 0.0f;
    } else r = 0;
    return r;
}

extern int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(float *dir, float *cur, float *aim);

int GAMEUTIL_near_to_aim_yaw_dir(float *dir, int *rot, s128 *cur, float *aim)
{
    Vec4 tmp;
    int r;
    tmp.q = *cur;
    r = GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(dir, tmp.f, aim);
    if (rot) *rot = r;
    if (is_yaw_dir_sandwich(aim, tmp.f, dir) == 1) {
        if (dir) *(s128 *)dir = *(s128 *)aim;
        return 1;
    }
    return 0;
}
#endif
