typedef union {
    int q __attribute__((mode(TI)));
    float v[4];
} s128;

typedef struct WindVolume {
    int x0;
    int x4;
    int x8;
    float xC;
    float x10;
} WindVolume;

typedef struct WindParam {
    int x0;
    float x4;
    float x8;
    float xC;
    s128 pos;
    s128 rot;
    s128 x30;
} WindParam;

typedef struct Layout {
    char pad0[0x90];
    s128 x90;
    char padA0[0x134 - 0xA0];
    s128 *pos;
    int pad138;
    s128 *rot;
} Layout;

typedef struct WindEmitter {
    int type;
    WindVolume *volume;
    int x8;
    int padC;
    char geometry[0x50];
    WindParam param;
    int active;
    float xA4;
    int padA8[2];
    s128 pos;
    s128 dir;
    float xD0;
    int padD4[3];
    s128 up;
    int xF0;
    int xF4;
    int xF8;
    int padFC;
    int x100;
} WindEmitter;

typedef union {
    Layout s;
} LayoutU;

typedef union {
    WindVolume s;
} WindVolumeU;

typedef union {
    WindEmitter s;
} WindEmitterU;

extern Layout *GetLayoutClass(int);
extern int ScriptAnimationObjOfJudgeVolumeObject(void *, int);

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

static inline int updateWindTimer(WindEmitter *e, float dt)
{
    int state = e->active;

    if (state == 1) {
        float lim = e->volume->xC;

        if (0.0f < lim) {
            float t = e->xA4 + dt;

            e->xA4 = t;
            if (lim < t) {
                e->active = 0;
                state = 0;
            }
        }
    }
    return state;
}

static void func_000CC018(WindEmitter *e, int force, float dt)
{
    WindVolume *vol;
    WindParam *param;
    Layout *layout;
    char buf[0x60];

    updateWindTimer(e, dt);
    if (((WindEmitterU *)e)->s.active == 1 && e->x100 != 0) {
        param = &e->param;
        layout = GetLayoutClass(e->x100);
        if (ScriptAnimationObjOfJudgeVolumeObject(buf, e->x100) == 1) {
            param->x4 = *(float *)(buf + 0x5C);
        }
        param->x8 = param->xC = 0.0f;
        param->pos.q = ((LayoutU *)layout)->s.pos->q;
        param->rot.q = layout->rot->q;
        param->x30.q = layout->x90.q;
        vol = e->volume;
        if (vol->x8 == 1 || force == 1) {
            e->pos.q = param->pos.q;
        }
        quatAxisZ(e->dir.v, param->rot.v);
        e->xD0 = param->x4 * vol->x10;
        if (((WindVolumeU *)e->volume)->s.x4 == 0) {
            vecScale(e->up.v, e->dir.v, e->xD0);
        }
    }
}
