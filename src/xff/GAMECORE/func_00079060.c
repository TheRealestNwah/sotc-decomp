typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char gcGlobalVar[];
extern float get_merge_yaw_nico_yaw_pitch_cntrl(void *);
extern int is_enable_reach_src_yaw_nico_sight_on(float *, void *, float);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern void doit_double_spring_interp_cntrl(void *, int, float, float);
extern int get_predict_hit_position_nico_sight_on(void *, void *);
extern void get_radiate_direction_nico_sight_on(void *, void *);

static inline float dist3(Vec4 *a, Vec4 *b)
{
    float f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(f) : "r"(a), "r"(b) : "$2");
    return f;
}

static inline void scale3(Vec4 *out, Vec4 *a, float s)
{
    __asm__ __volatile__("mfc1 $2, %2\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "f"(s) : "$2", "memory");
}

static inline void lerp3(Vec4 *out, Vec4 *a, Vec4 *b, float t)
{
    register int ti __asm__("$8");
    __asm__("mfc1 %0, %1" : "=r"(ti) : "f"(t));
    __asm__ __volatile__("qmtc2.ni %3, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "r"(ti) : "memory");
}

static inline float distSq3(Vec4 *a, Vec4 *b)
{
    int bits;
    float f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni %0, vf7\n"
                         "mtc1 %0, %1\n"
                         : "=&r"(bits), "=f"(f)
                         : "r"(a), "r"(b)
                         : "memory");
    return f;
}

static void func_00079060(Vec4 *out, char *w, void *th)
{
    Vec4 res;
    Vec4 tmp;
    Vec4 hit;
    Vec4 dir;
    float yaw;
    float r;
    char *sight = w + 0x190;
    register Vec4 *pos __asm__("$4");

    yaw = 0.0f;
    r = 1.0f;
    if (!is_enable_reach_src_yaw_nico_sight_on(&yaw, sight, get_merge_yaw_nico_yaw_pitch_cntrl(w + 0x19C))) {
        float a = yaw;
        if (a < 0.0f)
            a = -a;
        r = r - GAMEUTIL_get_dist_ratio(a, 0.17453292012214661f, 0.61086518f);
    }
    doit_double_spring_interp_cntrl(w + 0x470, 0, r, *(float *)(gcGlobalVar + 0x180));
    get_predict_hit_position_nico_sight_on(&hit, sight);
    get_radiate_direction_nico_sight_on(&dir, sight);
    pos = (Vec4 *)(w + 0x4A0);
    scale3(&dir, &dir, dist3(pos, &hit));
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(&tmp), "r"(pos), "r"(&dir) : "memory");
    lerp3(&res, &hit, &tmp, *(float *)(w + 0x48C));
    if (distSq3(pos, &res) < 0.01f)
        res.q = hit.q;
    out->q = res.q;
    out->f[3] = 1.0f;
}
