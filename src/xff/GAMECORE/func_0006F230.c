/* Parked: 4 diffs, same size (213 words incl. the split tail func_0006F540). Sight-on camera yaw update: takes the actor's local Z direction (yaw/pitch at sp+0x20/0x24), aims from the target layout position (+0x29C height offset, VU0 vsub.xyz into +0x1F0) to get yaw/pitch at +0x200/+0x204, adds func_0006F578's offset into +0x208 and clamps it against +0x2C4..+0x2CC when +0x2BC or +0x2C0 is set. Mode 1 resets the two spring interpolators (+0x22C, +0x250); otherwise they are driven by gcGlobalVar.dt with the dead zone +0x2B0/+0x2B4, then +0x280 is clamped when +0x2B8 is set. Remaining: the yaw/pitch zero stores around the I(4) load (Original: lw first, then the 0x24 store and the a1 move, with the 0x20 store in the jal delay slot; ours fills the slot with the a1 move). Declaration order, store order, comma expressions, barriers and a $f0 pin don't move it. The $f1 pin on the +0x208 load in the dead-zone-free path is needed. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union {
    struct {
        float x, y, z, w;
    } v;
    s128 q;
} Vec;

extern struct { char pad[0x180]; float dt; } gcGlobalVar;
extern void GAMEUTIL_get_local_directionZ(void *, int);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, void *);
extern void *memset(void *, int, unsigned int);
extern char *GetLayoutClass(int);
extern void GAMEUTIL_check_and_get_normalize_vector(void *, int, void *);
extern float func_0006F578(char *, float, float, int);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern float GAMEUTIL_get_limit_clip_yaw_abs(int, float, float, float, float);
extern void reset_double_spring_interp_cntrl(void *, float);
extern void reset_double_spring_interp_cntrl3D(void *, void *);
extern void doit_double_spring_interp_cntrl(void *, float, float, int);
extern void doit_double_spring_interp_cntrl3D(void *, void *, int, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);

#define F(o) (*(float *)(o_ + (o)))
#define I(o) (*(int *)(o_ + (o)))

static void func_0006F230(char *o_, float a, float b, int mode)
{
    Vec dir;
    Vec v;
    float yaw;
    float pitch;
    float y;
    float lo;
    float hi;
    float d;
    int in;
    char *n = o_ + 0x1F0;

    { int o4 = I(4);
    pitch = 0.0f;
    yaw = 0.0f;
    GAMEUTIL_get_local_directionZ(&dir, o4); }
    GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, &dir);
    y = yaw;
    memset(&v, 0, 0x10);
    dir.q = **(s128 **)(GetLayoutClass(I(4)) + 0x134);
    dir.v.y += F(0x29C);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(n), "r"(o_ + 0x1D0), "r"(&dir) : "memory");
    GAMEUTIL_check_and_get_normalize_vector(n, 0, n);
    GAMEUTIL_get_yaw_pitch_by_direction((float *)(o_ + 0x200), (float *)(o_ + 0x204), n);
    F(0x208) = GAMEUTIL_increase_yaw(0, F(0x200), func_0006F578(o_, a, b, mode));
    if (I(0x2BC) == 1 || I(0x2C0) == 1) {
        lo = GAMEUTIL_increase_yaw(0, y, F(0x2C4));
        hi = GAMEUTIL_increase_yaw(0, y, F(0x2C8));
        F(0x208) = GAMEUTIL_get_limit_clip_yaw_abs(0, F(0x208), lo, hi, GAMEUTIL_increase_yaw(0, y, F(0x2CC)));
    }
    if (mode == 1) {
        reset_double_spring_interp_cntrl(o_ + 0x22C, 0.0f);
        v.v.x = y;
        reset_double_spring_interp_cntrl3D(o_ + 0x250, &v);
        return;
    }
    v.v.y = F(0x204);
    if (F(0x2B0) == 0.0f && F(0x2B4) == 0.0f) {
        doit_double_spring_interp_cntrl(o_ + 0x22C, 0.0f, gcGlobalVar.dt, 0);
        { register float t asm("$f1") = F(0x208); v.v.x = t; }
        doit_double_spring_interp_cntrl3D(o_ + 0x250, &v, 0, gcGlobalVar.dt);
    } else {
        in = 1;
        d = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(F(0x280), F(0x208));
        if (0.0f <= d) {
            if (d < F(0x2B0))
                in = 0;
        } else if (F(0x2B4) < d)
            in = 0;
        {
            float x = in == 1 ? F(0x248) : d;
            doit_double_spring_interp_cntrl(o_ + 0x22C, x, gcGlobalVar.dt, 0);
        }
        if (in == 1)
            v.v.x = GAMEUTIL_increase_yaw(0, F(0x208), -F(0x248));
        else
            v.v.x = F(0x280);
        doit_double_spring_interp_cntrl3D(o_ + 0x250, &v, 0, gcGlobalVar.dt);
    }
    if (I(0x2B8) == 1) {
        lo = GAMEUTIL_increase_yaw(0, y, F(0x2C4));
        hi = GAMEUTIL_increase_yaw(0, y, F(0x2D0));
        F(0x280) = GAMEUTIL_get_limit_clip_yaw_abs(0, F(0x280), lo, hi, GAMEUTIL_increase_yaw(0, y, F(0x2D4)));
    }
}
#endif
