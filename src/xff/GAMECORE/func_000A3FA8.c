typedef struct {
    float angle;
    float f04;
    float f08;
    float f0C;
    float f10;
    char pad14[0x1C - 0x14];
    float f1C;
    float f20;
    char pad24[0x30 - 0x24];
} MoveParamA3FA8;

typedef struct {
    char pad00[0x18];
    float range;
    char pad1C[0x40 - 0x1C];
    char sub40[0x80 - 0x40];
    float angle80;
    float f84;
    float f88;
    float f8C;
    char pad90[0xEC - 0x90];
    float fEC;
    float fF0;
    char padF4[0x100 - 0xF4];
    float angle100;
} DefA3FA8;

typedef struct {
    char pad00[0x20];
    DefA3FA8 *def;
    char pad24[0x40 - 0x24];
    int mode;
    char pad44[0x110 - 0x44];
    char pos[0x1D0 - 0x110];
    char rot[0x2B8 - 0x1D0];
    char vel0[0x2C8 - 0x2B8];
    char vel1[0x310 - 0x2C8];
    float speed;
} ObjA3FA8;

typedef union {
    ObjA3FA8 s;
} ObjA3FA8U;

extern float func_000A3AA0(void *, float);
extern void AI_GetRandomVelocity(void *, void *, void *, float, float, float, float);
extern void func_000A33F8(void *, void *, void *, void *, void *);

static void func_000A3FA8(ObjA3FA8 *obj)
{
    MoveParamA3FA8 param;
    float t = func_000A3AA0(obj, obj->def->f8C);
    DefA3FA8 *def;

    if (t != 0.0f) {
        obj->speed = 1.0f;
    } else {
        float r = obj->def->range;

        AI_GetRandomVelocity(&obj->speed, obj->vel0, obj->vel1, 1.0f - r, r + 1.0f, 1.0f, 5.0f);
    }
    def = obj->def;
    param.f04 = def->f84;
    param.f08 = obj->speed + t;
    param.f0C = 2.0f;
    param.f10 = def->f88;
    if (((ObjA3FA8U *)obj)->s.mode != 0) {
        param.angle = def->angle100 * 0.017453293f;
        param.f1C = def->fF0;
        param.f20 = def->fEC;
    } else {
        param.angle = def->angle80 * 0.017453293f;
        param.f20 = 0.0f;
        param.f1C = 1.0f;
    }
    func_000A33F8(obj, obj->pos, obj->rot, &param, def->sub40);
}

typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct { char pad[0x190]; float delta; } GlobalVar;
extern GlobalVar gcGlobalVar;
extern float AI_GetRotVelocity(float, float, float, float);
extern int AI_GetSideSignalFromDirLev(void *, void *);
extern void AI_UpdateVelocity(void *, float, float);
extern char *GetLayoutClass(void *);
extern float func_000A3E08(char *, float);
extern void func_000A40D0(float, char *, float *, char *, int);
extern float iosGetACosfExact(float);
extern float iosGetASinfExact(float);
extern float iosGetTableSin(short);
extern float iosGetTableCos(short);

static inline float dot3(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline float length3(void *a)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a) : "$2");
    return d;
}

static void func_000A4858(char *w, char *p)
{
    float dir[4] __attribute__((aligned(16)));
    Vec4 v;
    Vec4 lay;
    float lo, hi;
    float dot, ang, side;
    Vec4 *vp; float off, mul, rt, kmax, lim, zero, pitch; char *vel;
    float s, a, t, len, push, spd, base, r;
    float *yaw;
    float u;
    char *k, *k1, *k2, *k3;
    char *q;

    if (*(int *)(w + 0x38) == 0) {
        lo = *(float *)(*(char **)(w + 0x20) + 0x12C);
        hi = *(float *)(*(char **)(w + 0x20) + 0x130);
        AI_GetRandomVelocity(w + 0x2D0, w + 0x2B0, w + 0x2C0, lo - hi, lo + hi, 1.0f, 5.0f);
    }
    func_000A40D0(*(float *)(w + 0x2D0), w, dir, p, *(int *)(w + 0x794));
    k1 = *(char **)(w + 0x20);
    a = *(float *)(k1 + 0xAC);
    s = *(float *)(k1 + 0xB0);
    dot = dot3(dir, w + 0x240);
    ang = iosGetACosfExact(dot);
    side = AI_GetSideSignalFromDirLev(w + 0x240, dir);
    base = 1.0f - (dot + 1.0f) * 0.5f;
    *(float *)(w + 0x2F0) = dot;
    *(float *)(w + 0x2F4) =
        AI_GetRotVelocity(*(float *)(w + 0x2F4) * 90.0f * 3.14159265f / 180.0f, ang * side, a, s) * 180.0f /
        282.74332f;
    vp = &v;
    lay.q = **(s128 **)(GetLayoutClass(isysGetThisSubThread()) + 0x134);
    kmax = 0.34202012f;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(vp) : "memory");
    v.f[1] = -*(float *)(p + 0x48) / *(float *)(p + 0x40);
    if ((v.f[1] < 0.0f ? -v.f[1] : v.f[1]) > kmax) {
        lim = 0.34202012f;
        if (v.f[1] < 0.0f)
            lim = -lim;
        v.f[1] = lim;
    }
    yaw = (float *)(w + 0x304);
    vel = w + 0x2FC;
    k2 = *(char **)(w + 0x20);
    off = *(float *)(k2 + 0x80) * 0.017453293f;
    mul = *(float *)(k2 + 0x84);
    pitch = iosGetASinfExact(v.f[1]) + off;
    if (pitch > 1.5707963f)
        pitch = 1.5707963f;
    else if (pitch < -1.5707963f)
        pitch = -1.5707963f;
    *(float *)(w + 0x300) = pitch;
    {
        register float c __asm__("$f15");
        register float d __asm__("$f14");
        register float b __asm__("$f13");
        register float a __asm__("$f12");
        a = *(float *)(w + 0x2F8);
        b = *yaw;
        d = 3.0f;
        c = 0.1f;
        t = AI_GetRotVelocity(a, pitch - b, d, c);
    }
    *(float *)(w + 0x2F8) = t;
    AI_UpdateVelocity(vel, (*yaw = *yaw + t * gcGlobalVar.delta) * mul, 0.1f);
    k = *(char **)(w + 0x20);
    q = k + 0x40;
    len = length3(w + 0x2E0);
    push = -len * *(float *)(k + 0x20);
    zero = 0.0f;
    if (*(float *)(w + 0x2E8) < zero)
        push = -push;
    s = iosGetTableSin((short)(int)(*(float *)(w + 0x300) * 32768.0f / 3.14159265f));
    k3 = *(char **)(w + 0x20);
    len = len + ((*(float *)(q + 8) * (*(float *)(w + 0x314) - *(float *)(w + 0x318)) +
            -*(float *)(k3 + 0x24) * *(float *)(k3 + 0x1C) * s * *(float *)(q + 4) + push) /
           *(float *)(k3 + 0x1C)) * gcGlobalVar.delta;
    spd = len;
    *(float *)(w + 0x2E4) = spd * iosGetTableSin((short)(int)(*(float *)(w + 0x304) * 32768.0f / 3.14159265f));
    *(float *)(w + 0x2E8) = spd * iosGetTableCos((short)(int)(*(float *)(w + 0x304) * 32768.0f / 3.14159265f));
    u = func_000A3E08(w, *(float *)(*(char **)(w + 0x20) + 0xA0)) + 1.0f;
    *(float *)(w + 0x310) = 1.0f;
    r = *(float *)(*(char **)(w + 0x20) + 0x40);
    AI_UpdateVelocity(w + 0x314, u + *(float *)(w + 0x300) / 1.5707963f, 2.0f);
    {
        register float lim __asm__("$f1") = *(float *)(w + 0x7E8);
        spd = spd / (*(float *)(*(char **)(w + 0x20) + 0x28) * lim);
    }
    AI_UpdateVelocity(w + 0x318, base * (spd * spd) * r, 2.0f);
    *(float *)(w + 0x30C) = *(float *)(w + 0x314) + *(float *)(w + 0x318) + zero;
}

typedef struct {
    float angle;
    float f04;
    float f08;
    float f0C;
    float f10;
    char pad14[0x1C - 0x14];
    float f1C;
    float f20;
    char pad24[0x30 - 0x24];
} MoveParam;

typedef struct {
    int pad0;
    int status;
} ScriptCtrlDef;

#define I(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
typedef union {
    float f;
    int i;
} FloatOrInt;
#define IU(p, o) (((FloatOrInt *)((char *)(p) + (o)))->i)

extern void *isysGetThisSubThread(void);
extern void func_000A4D58(char *, char *);
extern void func_000A4370(char *, char *);
extern void func_000A5260(char *, char *);
extern void func_000A5660(char *, char *);
extern void func_000A5900(char *, char *);
extern void SCRSetCharaMotionPlaySpeedRatioDirect(void *, float);
extern void CharaCtrlSetOutsideScriptCtrlStatus(int, int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern ScriptCtrlDef *ScriptCtrlDef_SCRPlayerAnimalLandHit;
extern ScriptCtrlDef *ScriptCtrlDef_SCRJump;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFlapWing;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFly;
extern ScriptCtrlDef *ScriptCtrlDef_SCRGlide;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStop;
extern ScriptCtrlDef *ScriptCtrlDef_SCRDeath;

/* Defined after its callees func_000A3FA8 and func_000A4858: with them in
   the same file, the I580 test in case 4 gets the Original's beqz.
   The flag at 0x40 is read through a union so gcc may not move it past the
   float stores (strict aliasing), as in the Original. */
static void func_000A8C48(char *w)
{
    void *th = isysGetThisSubThread();
    MoveParam p;
    int v;

    switch (I(w, 0x26C)) {
    case 0:
        if (I(w, 0x27C) == 2)
            I(w, 0x284) = 0x16;
        else
            I(w, 0x284) = 0x1A;
        break;
    case 2:
        p.f0C = 2.0f;
        F(w, 0x310) = 1.0f;
        p.angle = 0.0f;
        p.f04 = 1.0f;
        p.f08 = 1.0f;
        p.f10 = 0.0f;
        if (IU(w, 0x40))
            p.f1C = F(P(w, 0x20), 0xF0);
        else
            p.f1C = 1.0f;
        p.f20 = 0.0f;
        func_000A33F8(w, w + 0x110, w + 0x1D0, &p, P(w, 0x20) + 0x30);
        F(w, 0x30C) = 1.0f;
        I(w, 0x284) = 0x17;
        break;
    case 4:
        if (I(w, 0x274) == 1)
            func_000A4858(w, w + 0x170);
        else if (I(w, 0x580))
            func_000A3FA8((ObjA3FA8 *)w);
        else
            func_000A4858(w, w + 0x170);
        v = I(w, 0x27C);
        if (v == 6)
            I(w, 0x284) = 0x19;
        else if (v == 5)
            I(w, 0x284) = 0x19;
        else if (v == 9)
            I(w, 0x284) = 0x19;
        else
            I(w, 0x284) = 0x18;
        break;
    case 6:
        if (I(w, 0x274) == 1)
            func_000A4858(w, w + 0x170);
        else if (I(w, 0x580)) {
            F(w, 0x310) = 1.0f;
            p.f04 = F(P(w, 0x20), 0x94);
            p.f08 = F(w, 0x310) + func_000A3AA0(w, F(P(w, 0x20), 0x9C));
            p.f0C = 0.5f;
            p.f10 = F(P(w, 0x20), 0x98);
            if (IU(w, 0x40)) {
                p.angle = F(P(w, 0x20), 0x104) * 0.01745329252f;
                p.f1C = F(P(w, 0x20), 0xF0);
                p.f20 = F(P(w, 0x20), 0xEC);
            } else {
                p.angle = F(P(w, 0x20), 0x90) * 0.01745329252f;
                p.f1C = 1.0f;
                p.f20 = 0.0f;
            }
            func_000A33F8(w, w + 0x110, w + 0x1D0, &p, P(w, 0x20) + 0x50);
        } else
            func_000A4D58(w, w + 0x170);
        v = I(w, 0x27C);
        if (v == 4)
            I(w, 0x284) = 0x18;
        else if (v == 5)
            I(w, 0x284) = 0x19;
        else if (v == 9)
            I(w, 0x284) = 0x19;
        else
            I(w, 0x284) = 0x19;
        break;
    case 7:
        F(w, 0x310) = 1.0f;
        p.f04 = 1.0f;
        p.f08 = F(w, 0x310) + func_000A3AA0(w, F(P(w, 0x20), 0x9C));
        p.f0C = 2.0f;
        p.f10 = F(P(w, 0x20), 0x88);
        if (IU(w, 0x40)) {
            p.angle = F(P(w, 0x20), 0x100) * 0.01745329252f;
            p.f1C = F(P(w, 0x20), 0xF0);
            p.f20 = F(P(w, 0x20), 0xEC);
        } else {
            p.f1C = 1.0f;
            p.angle = 0.0f;
            p.f20 = 0.0f;
        }
        func_000A33F8(w, w + 0x110, w + 0x1D0, &p, P(w, 0x20) + 0x40);
        if (I(w, 0x27C) == 4)
            I(w, 0x284) = 0x18;
        break;
    case 5:
        func_000A4370(w, w + 0x170);
        v = I(w, 0x27C);
        if (v == 4)
            I(w, 0x284) = 0x18;
        else if (v == 6)
            I(w, 0x284) = 0x19;
        else if (v == 9)
            I(w, 0x284) = 0x19;
        else
            I(w, 0x284) = 0x19;
        break;
    case 9:
        func_000A5260(w, w + 0xB0);
        v = I(w, 0x27C);
        if (v == 10)
            I(w, 0x284) = 0x19;
        else if (v == 4)
            I(w, 0x284) = 0x18;
        else if (v == 14)
            I(w, 0x284) = 0x1A;
        else if (v == 15)
            I(w, 0x284) = 0x19;
        else if (v == 13)
            I(w, 0x284) = 0x18;
        else if (F(w, 0x2F4) < 0.0f ? F(w, 0x2F4) < -0.5f : 0.5f < F(w, 0x2F4))
            I(w, 0x284) = 0x18;
        else
            I(w, 0x284) = 0x19;
        break;
    case 13:
        func_000A3FA8((ObjA3FA8 *)w);
        v = I(w, 0x27C);
        if (v == 4)
            I(w, 0x284) = 0x18;
        else if (v == 9)
            I(w, 0x284) = 0x19;
        else if (v == 14)
            I(w, 0x284) = 0x1A;
        else
            I(w, 0x284) = 0x18;
        break;
    case 14:
        func_000A5660(w, w + 0xB0);
        if (I(w, 0x27C) == 0)
            I(w, 0x284) = 0x15;
        else
            I(w, 0x284) = 0x1A;
        break;
    case 15:
        func_000A5900(w, w + 0xB0);
        if (I(w, 0x27C) == 16)
            I(w, 0x284) = 0x19;
        else
            I(w, 0x284) = 0x19;
        break;
    case 16:
        F(w, 0x310) = 1.0f;
        p.f0C = 2.0f;
        p.f04 = 1.0f;
        p.f08 = 1.0f;
        p.f10 = 1.0f;
        if (IU(w, 0x40)) {
            p.angle = 0.0f;
            p.f1C = F(P(w, 0x20), 0xF0);
            p.f20 = F(P(w, 0x20), 0xEC);
        } else {
            p.f1C = 1.0f;
            p.angle = 0.1745329252f;
            p.f20 = 0.0f;
        }
        func_000A33F8(w, w + 0x110, w + 0x1D0, &p, P(w, 0x20) + 0x40);
        if (I(w, 0x27C) == 4)
            I(w, 0x284) = 0x18;
        else
            I(w, 0x284) = 0x18;
        break;
    case 18:
        SCRSetCharaMotionPlaySpeedRatioDirect(th, 1.0f);
        I(w, 0x284) = 0x1B;
        break;
    case 19:
        CharaCtrlSetOutsideScriptCtrlStatus(I(w, 0x24), ScriptCtrlDef_SCRPlayerAnimalLandHit->status);
        SCRSetCharaMotionPlaySpeedRatioDirect(th, 1.0f);
        I(w, 0x284) = 0x1B;
        break;
    case 20:
        if (I(w, 0x27C) == 4)
            I(w, 0x284) = 0x18;
        break;
    }
    v = I(w, 0x7BC);
    if (v >= 2)
        I(w, 0x284) = 0x1B;
    if (v > 0)
        I(w, 0x7BC) = v + 1;
    switch (I(w, 0x284)) {
    case 0x15:
        break;
    case 0x16:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRJump->status);
        break;
    case 0x17:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRFlapWing->status);
        break;
    case 0x18:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRFly->status);
        break;
    case 0x19:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGlide->status);
        break;
    case 0x1A:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRStop->status);
        break;
    case 0x1B:
        CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRDeath->status);
        break;
    }
}
