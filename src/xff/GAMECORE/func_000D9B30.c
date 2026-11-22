/* Parked: 19 diffs, same size. Cliff-rise camera probe: a state machine on p+0x140. State 0 copies the cliff-rise parameters (angles converted to radians, distances scaled by 0.6 while delayed) and casts a probe forward from the target position; state 1 steps along the probe, ray-casting downward at 60 degrees through func_000DA638 and keeping the steepest rise angle; state 2 casts toward the highest hit to find the camera point and its weight; state 3 checks the step beyond it. States 4 and 5 publish the result to p+0x160 and arm the hold timer at p+0x150. Remaining: the Original loads prm+0x114 in the jal delay slot after the float copies (ours hoists it), sets t0 instead of v1 for the 0.95 lerp factor with addiu v0,sp,0x40 before the lui, and orders the state 5 stores lq/sw 1E0/sq 1D0/sw 1E4. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

typedef struct {
    char pad[0x40];
    Vec pos;
} Hit;

extern s128 ZeroPoint;
extern int is_cliff_rise_ok_camera_place_status(void *);
extern int is_cliff_rise_delay_camera_place_status(void *);
extern float GetPlaneSlopeDegree(void *);
extern void func_000D98F0(char *);
extern int func_000DA638(void *, void *, void *, char *, void *);
extern void *CAM_get_target_riding_obj(void *);
extern int player_collision_check_direct(void *, void *, void *, void *, void *, int);
extern float iosGetTanf(float);
extern float iosGetATanfExact(float);

#define V(o) (*(s128 *)(p + (o)))
#define F(o) (*(float *)(p + (o)))
#define I(o) (*(int *)(p + (o)))

#define SUB(o, a, b)                                                                     \
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"                                           \
                         "lqc2 vf6, 0x0(%2)\n"                                           \
                         "vsub.xyz vf5, vf5, vf6\n"                                      \
                         "sqc2 vf5, 0x0(%0)\n"                                           \
                         :                                                               \
                         : "r"(o), "r"(a), "r"(b)                                        \
                         : "memory")
#define ADD(o, a, b)                                                                     \
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"                                           \
                         "lqc2 vf6, 0x0(%2)\n"                                           \
                         "vadd.xyz vf5, vf5, vf6\n"                                      \
                         "sqc2 vf5, 0x0(%0)\n"                                           \
                         :                                                               \
                         : "r"(o), "r"(a), "r"(b)                                        \
                         : "memory")
#define SCALE(o, a, s)                                                                   \
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"                                           \
                         "qmtc2 %2, vf6\n"                                               \
                         "vmulx.xyz vf5, vf5, vf6x\n"                                    \
                         "sqc2 vf5, 0x0(%0)\n"                                           \
                         :                                                               \
                         : "r"(o), "r"(a), "r"(s)                                        \
                         : "memory")
#define LERP(o, a, b, t)                                                                 \
    __asm__ __volatile__("qmtc2 %3, vf7\n"                                               \
                         "lqc2 vf5, 0x0(%1)\n"                                           \
                         "lqc2 vf6, 0x0(%2)\n"                                           \
                         "vsubx.w vf8, vf0, vf7x\n"                                      \
                         "vmulax.xyz ACC, vf5, vf7x\n"                                   \
                         "vmaddw.xyz vf5, vf6, vf8w\n"                                   \
                         "sqc2 vf5, 0x0(%0)\n"                                           \
                         :                                                               \
                         : "r"(o), "r"(a), "r"(b), "r"(t)                                \
                         : "memory")
#define DISTXZ(r, a, b)                                                                  \
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"                                           \
                         "lqc2 vf6, 0x0(%2)\n"                                           \
                         "vsub.xyzw vf7, vf5, vf6\n"                                     \
                         "vmul.xz vf7, vf7, vf7\n"                                       \
                         "vaddz.x vf7, vf7, vf7z\n"                                      \
                         "vsqrt Q, vf7x\n"                                               \
                         "vwaitq\n"                                                      \
                         "cfc2 $2, $vi22\n"                                              \
                         "mtc1 $2, %0\n"                                                 \
                         : "=f"(r)                                                       \
                         : "r"(a), "r"(b)                                                \
                         : "$2")
#define LENGTH(r, a)                                                                     \
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"                                           \
                         "vmul.xyz vf7, vf7, vf7\n"                                      \
                         "vmulax.w ACC, vf0, vf7x\n"                                     \
                         "vmadday.w ACC, vf0, vf7y\n"                                    \
                         "vmaddz.w vf7, vf0, vf7z\n"                                     \
                         "vsqrt Q, vf7w\n"                                               \
                         "vwaitq\n"                                                      \
                         "cfc2 $2, $vi22\n"                                              \
                         "mtc1 $2, %0\n"                                                 \
                         : "=f"(r)                                                       \
                         : "r"(a)                                                        \
                         : "$2")

void func_000D9B30(char *p, char *cam, Vec *dir, void *c, float dt)
{
    Hit hit;
    Vec b;
    Vec a;
    Vec t;
    Vec u;
    int ok;
    int s;
    int done;
    int fail;
    int n;
    int r;
    char *q;
    char *prm;
    float d;
    float h;
    float e;
    float lo;
    float k;

    ok = is_cliff_rise_ok_camera_place_status(cam + 0x1270);
    if (ok == 1) {
        s = I(0x140);
        done = 0;
        if (s == 0) {
            q = p + 0xC0;
            if (*(int *)(q + 8) == 1) {
                if (GetPlaneSlopeDegree(p + 0xE0) <= 80.0f) {
                    prm = *(char **)cam;
                    k = 0.0174532925f;
                    F(0x1E8) = *(float *)(prm + 0x100) * k;
                    F(0x1EC) = *(float *)(prm + 0x104);
                    F(0x1F0) = *(float *)(prm + 0x108) * k;
                    F(0x1F4) = *(float *)(prm + 0x10C);
                    F(0x1F8) = *(float *)(prm + 0x110);
                    I(0x1FC) = *(int *)(prm + 0x114);
                    if (is_cliff_rise_delay_camera_place_status(cam + 0x1270) == 1) {
                        F(0x1F4) = F(0x1F4) * 0.6f;
                        F(0x1F8) = F(0x1F8) * 0.6f;
                    }
                    V(0x180) = *(s128 *)(q + 0x40);
                    SCALE(&t, dir, F(0x1F4));
                    ADD(p + 0x190, p + 0x180, &t);
                    if (player_collision_check_direct(&hit, p + 0x180, p + 0x190, c, CAM_get_target_riding_obj(cam + 0x23C), 1) == 1)
                        LERP(p + 0x190, &hit.pos, p + 0x180, 0.95f);
                    I(0x140) = 1;
                    V(0x1A0) = *(s128 *)(q + 0x30);
                    I(0x144) = 0;
                    F(0x1C0) = 0.0f;
                } else {
                    func_000D98F0(p);
                }
            }
        } else if (s == 1) {
            n = I(0x144);
            fail = 0;
            if (n < I(0x1FC)) {
                SUB(&u, p + 0x190, p + 0x180);
                SCALE(&u, &u, (float)(I(0x144) + 1) / (float)I(0x1FC));
                ADD(&a, p + 0x180, &u);
                DISTXZ(d, p + 0x180, &a);
                k = iosGetTanf(1.04719755f);
                b.q = a.q;
                b.y = F(0x1A4) - d * k;
                if (func_000DA638(&hit, &a, &b, cam, c) == 1) {
                    h = F(0x1A4) - hit.pos.y;
                    if (0.0f < h) {
                        float at = iosGetATanfExact(h / d);
                        if (F(0x1C0) < at) {
                            F(0x1C0) = at;
                            V(0x1B0) = hit.pos.q;
                        }
                    }
                    V(0x230) = hit.pos.q;
                    I(0x220) = 1;
                } else {
                    fail = 1;
                    F(0x1C0) = 1.04719755f;
                    V(0x1B0) = b.q;
                    I(0x220) = 0;
                }
                V(0x210) = b.q;
                V(0x200) = a.q;
                I(0x144) = I(0x144) + 1;
                n = I(0x144);
            }
            if (n >= I(0x1FC))
                fail = 1;
            if (fail == 1) {
                if (F(0x1C0) > F(0x1E8))
                    I(0x140) = 2;
                else
                    I(0x140) = 5;
            }
        } else if (s == 2) {
            b.q = V(0x1A0);
            b.y = b.y - 0.1f;
            a.q = V(0x1B0);
            {
                float tn = iosGetTanf(F(0x1E8));
                float dd;
                DISTXZ(dd, p + 0x1A0, p + 0x1B0);
                a.y = F(0x1A4) - tn * dd - 0.1f;
            }
            if (player_collision_check_direct(&hit, &a, &b, c, CAM_get_target_riding_obj(cam + 0x23C), 1) == 1) {
                V(0x1D0) = hit.pos.q;
            } else {
                SUB(&t, &b, &a);
                SCALE(&t, &t, 0.99f);
                ADD(p + 0x1D0, &a, &t);
            }
            {
                float dd;
                DISTXZ(dd, p + 0x1A0, p + 0x1D0);
                lo = F(0x1F8);
                if (dd <= lo)
                    F(0x1E0) = 1.0f;
                else
                    F(0x1E0) = 1.0f - (dd - lo) / (F(0x1F4) - lo);
            }
            F(0x1E4) = F(0x1C0);
            I(0x140) = 3;
            V(0x240) = a.q;
            V(0x250) = b.q;
            I(0x260) = 1;
            V(0x270) = V(0x1D0);
        } else if (s == 3) {
            e = F(0x1F4) / (float)I(0x1FC);
            SUB(&t, p + 0x1B0, p + 0x1A0);
            t.y = 0.0f;
            {
                float ln;
                LENGTH(ln, &t);
                SCALE(&t, &t, e / ln);
            }
            ADD(&b, p + 0x1D0, &t);
            b.y = b.y - iosGetTanf(F(0x1E8)) * e;
            r = player_collision_check_direct(&hit, p + 0x1D0, &b, c, CAM_get_target_riding_obj(cam + 0x23C), 1);
            if (r == 1) {
                I(0x140) = 5;
                I(0x2A0) = r;
                V(0x2B0) = hit.pos.q;
            } else {
                I(0x2A0) = 0;
                I(0x140) = 4;
            }
            V(0x280) = V(0x1D0);
            V(0x290) = b.q;
        }
        s = I(0x140);
        if (s == 4) {
            done = 1;
        } else if (s == 5) {
            done = 1;
            V(0x1D0) = ZeroPoint;
            F(0x1E0) = 0.0f;
            F(0x1E4) = 0.0f;
        }
        if (done == 1) {
            I(0x14C) = 1;
            V(0x160) = V(0x1D0);
            F(0x170) = F(0x1E0);
            F(0x174) = F(0x1E4);
            F(0x150) = 0.0f;
            I(0x140) = 0;
        } else if (I(0x14C) == 1) {
            F(0x150) = F(0x150) + dt;
            if (1.0f <= F(0x150)) {
                I(0x14C) = 0;
                F(0x150) = 0.0f;
            }
        } else {
            F(0x150) = 0.0f;
        }
    } else {
        func_000D98F0(p);
    }
}
#endif
