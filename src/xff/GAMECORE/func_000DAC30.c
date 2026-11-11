typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int act_approach_judge_ray_check_camera_target_approach(void *, void *, void *, int, char *, int);
extern int GAMEUTIL_get_cur_status_status_manager(int);
extern void GAMEUTIL_doit_status_manager(int, int, int, float);

static inline void sub3(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float dot3(Vec4 *a, Vec4 *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         : "=r"(d) : "r"(a), "r"(b));
    return d;
}

#ifdef NONMATCHING /* 17 diffs: register numbering only (original s3=flag, s4=arg1; a0/v1/v0 for &d1/&d2/the dot result) */
static void func_000DAC30(int arg0, char *arg1, int unused, int arg3, float fp)
{
    Vec4 v0[3];
    Vec4 v30;
    Vec4 v40;
    Vec4 d1;
    Vec4 d2;
    int flag = 0;
    float z;

    if (act_approach_judge_ray_check_camera_target_approach(v0, &v30, &v40, arg0, arg1, arg3) == 0) {
        Vec4 *p = (Vec4 *)(arg1 + 0x60);

        if (GAMEUTIL_get_cur_status_status_manager(arg0) == 1 || p->f[0x34 / 4] <= -0.6981317f ||
            (sub3(&d1, p, &v30), sub3(&d2, p, &v40), z = 0.0f, d2.f[1] = z, d1.f[1] = z, dot3(&d1, &d2) <= z)) {
            flag = 1;
        }
    }
    GAMEUTIL_doit_status_manager(arg0, flag, 0, fp);
}
#endif
