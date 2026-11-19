typedef int s128 __attribute__((mode(TI)));
extern int is_doing_nico_sight_on(void *);
extern void reset_double_spring_interp_cntrl(void *, float);
extern void GAMEUTIL_get_1p_left_analog_input_extend(float *, float *, int, float);
extern float GetWeaponRange(void);
extern void doit_nico_sight_on(void *, float, float, float);
extern char *GetLayoutClass(void *);
extern void sprWeaponSetMarker(void *, void *, int);
extern s128 ZeroPoint;
extern void func_00079220(void *, void *);
#ifdef NONMATCHING
static void func_00079060(float *, char *, void *);
#else
extern void func_00079060(float *, char *, void *);
#endif

static void func_00078F30(void *ctx, char *c)
{
    float in[2];
    int on;

    *(s128 *)(c + 0x40) = *(s128 *)(c + 0x30);
    c[0x51] = c[0x50];
    on = is_doing_nico_sight_on(c + 0x190);
    if (on == 1) {
        GAMEUTIL_get_1p_left_analog_input_extend(in, in + 1, 0, 0.3f);
        if (*(int *)(c + 0x180) == 0) {
            func_00079220(ctx, c);
            doit_nico_sight_on(c + 0x190, GetWeaponRange(), in[0], in[1]);
        }
        func_00079060((float *)(c + 0x30), c, ctx);
        c[0x50] = on;
        sprWeaponSetMarker(c + 0x30, *(void **)(GetLayoutClass(ctx) + 0x134), 1);
        *(int *)(c + 0x188) = on;
    } else {
        reset_double_spring_interp_cntrl(c + 0x470, 1.0f);
        {
            s128 z = ZeroPoint;
            c[0x50] = 0;
            *(s128 *)(c + 0x30) = z;
        }
        sprWeaponSetMarker(0, 0, 0);
    }
}

#ifdef NONMATCHING /* 2 diffs: the final swc1 1.0f,0xC(out) is scheduled before `ld s0` in the epilogue; the Original stores it after. Hand variants (s128 out, a `one` local, a Vec4 struct) and the permuter found nothing better. Aim at the hit position from the reach ratio (nico sight-on). */
typedef struct { char pad[0x180]; float f180; } GcG;
extern GcG gcGlobalVar;
extern float get_merge_yaw_nico_yaw_pitch_cntrl(void *);
extern int is_enable_reach_src_yaw_nico_sight_on(float *, float, void *);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern void doit_double_spring_interp_cntrl(void *, float, float, int);
extern void get_predict_hit_position_nico_sight_on(void *, void *);
extern void get_radiate_direction_nico_sight_on(void *, void *);

static void func_00079060(float *out, char *c, void *ctx)
{
    float res[4] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    float hit[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float *hp;
    float *dp;
    float d;
    float ratio;
    float len;
    float dist2;
    char *p;
    float t;

    d = 0.0f;
    ratio = 1.0f;
    if (is_enable_reach_src_yaw_nico_sight_on(&d, get_merge_yaw_nico_yaw_pitch_cntrl(c + 0x19C), c + 0x190) == 0) {
        ratio = 1.0f - GAMEUTIL_get_dist_ratio(d < 0.0f ? -d : d, 0x1.657184p-3f, 0.6108652f);
    }
    doit_double_spring_interp_cntrl(c + 0x470, ratio, gcGlobalVar.f180, 0);
    hp = hit;
    get_predict_hit_position_nico_sight_on(hp, c + 0x190);
    dp = dir;
    get_radiate_direction_nico_sight_on(dp, c + 0x190);
    p = c + 0x4A0;
    __asm__ volatile("lqc2 vf5, 0x0(%1)\n"
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
                     : "=f"(len) : "r"(p), "r"(hp) : "$2");
    __asm__ volatile("lqc2 vf5, 0x0(%0)\n"
                     "qmtc2.ni %1, vf6\n"
                     "vmulx.xyz vf5, vf5, vf6x\n"
                     "sqc2 vf5, 0x0(%0)\n"
                     : : "r"(dp), "r"(len) : "memory");
    __asm__ volatile("lqc2 vf5, 0x0(%1)\n"
                     "lqc2 vf6, 0x0(%2)\n"
                     "vadd.xyz vf5, vf5, vf6\n"
                     "sqc2 vf5, 0x0(%0)\n"
                     : : "r"(tmp), "r"(p), "r"(dp) : "memory");
    t = *(float *)(c + 0x48C);
    __asm__ volatile("mfc1 $8, %3
"
                     "qmtc2.ni $8, vf7
"
                     "lqc2 vf5, 0x0(%1)\n"
                     "lqc2 vf6, 0x0(%2)\n"
                     "vsubx.w vf8, vf0, vf7x\n"
                     "vmulax.xyz ACC, vf5, vf7x\n"
                     "vmaddw.xyz vf5, vf6, vf8w\n"
                     "sqc2 vf5, 0x0(%0)\n"
                     : : "r"(res), "r"(hp), "r"(tmp), "f"(t) : "$8", "memory");
    __asm__ volatile("lqc2 vf5, 0x0(%1)\n"
                     "lqc2 vf6, 0x0(%2)\n"
                     "vsub.xyzw vf7, vf5, vf6\n"
                     "vmul.xyz vf7, vf7, vf7\n"
                     "vaddy.x vf7, vf7, vf7y\n"
                     "vaddz.x vf7, vf7, vf7z\n"
                     "qmfc2.ni $2, vf7\n"
                     "mtc1 $2, %0\n"
                     : "=f"(dist2) : "r"(p), "r"(res) : "$2");
    if (dist2 < 0.01f)
        *(s128 *)res = *(s128 *)hit;
    *(s128 *)out = *(s128 *)res;
    out[3] = 1.0f;
}
#endif
