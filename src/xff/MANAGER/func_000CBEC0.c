typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[4];
    int noScale;
    int alwaysDir;
    float delay;
    float power;
} WindDef;

typedef union {
    WindDef s;
} WindDefU;

typedef struct {
    float f0;
    float power;
    float radius;
    float range;
    Vec4 dir;
    Vec4 quat;
} WindParam;

typedef struct {
    char pad0[4];
    WindDef *def;
    int wait;
    char padC[0x10 - 0xC];
    char src[0x60 - 0x10];
    WindParam param;
    char pad90[0xA0 - 0x90];
    int state;
    float time;
    char padA8[0xB0 - 0xA8];
    Vec4 dir;
    Vec4 axis;
    float power;
    char padD4[0xE0 - 0xD4];
    Vec4 force;
    char padF0[0x100 - 0xF0];
    float radiusSq;
    float rangeSq;
} Wind;

extern void GetScriptAnimationWindParam(WindParam *, void *);

static inline void quatAxisZ(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline int updateWindTimer(Wind *w, float dt)
{
    int state = w->state;

    if (state == 1) {
        float delay = w->def->delay;

        if (0.0f < delay) {
            float t = w->time + dt;

            w->time = t;
            if (delay < t) {
                w->state = 0;
                state = 0;
            }
        }
    }
    return state;
}

static void func_000CBEC0(Wind *w, int force, float dt)
{
    WindParam *p;
    int state = updateWindTimer(w, dt);
    WindDef *def;

    if (state != 1)
        return;
    p = &w->param;
    if (w->wait == state)
        GetScriptAnimationWindParam(p, w->src);
    def = w->def;
    if (def->alwaysDir == state || force == state)
        w->dir.q = p->dir.q;
    quatAxisZ(w->axis.f, p->quat.f);
    w->power = p->power * def->power;
    if (((WindDefU *)w->def)->s.noScale == 0)
        vecScale(w->force.f, w->axis.f, w->power);
    w->radiusSq = p->radius * p->radius;
    w->rangeSq = p->range * p->range;
}
