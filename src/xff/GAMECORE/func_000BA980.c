/* Parked at 6 diffs: the Original uses non-likely bne (li v0 in the delay slot) where a call result is stored into 0x16C (4 sites) and orders the case-2 AI_UpdateVelocity argument setup (a0 before the 0x5C load). Case 7 uses if/else for the bc1fl choice and a memory barrier after the 0x170 store to keep the 2.0f load after it. */
#ifdef NONMATCHING
typedef struct { int pad0; int status; } ScriptCtrlDef;
extern ScriptCtrlDef *ScriptCtrlDef_SCRStop;
extern ScriptCtrlDef *ScriptCtrlDef_SCRGoF;
extern ScriptCtrlDef *ScriptCtrlDef_SCRGoL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRGoR;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFastL;
extern ScriptCtrlDef *ScriptCtrlDef_SCRFastR;
extern ScriptCtrlDef *ScriptCtrlDef_SCRDeath;
extern int isysGetThisSubThread(void);
extern float iosGetRandom(void);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void AI_UpdateVelocity(void *, float, float);
extern void AI_GetRandomVelocity(float *, void *, void *, float, float, float, float);
extern void func_000B91C0(char *, float, float);
extern void func_000B93F0(char *, int, int);
extern void func_000B9548(char *, float, void *, float);
extern void func_000B9798(char *);
extern void func_000B9948(char *);
extern void func_000B9A38(char *);
extern void func_000B9B00(char *);
extern int func_000B9C98(char *);
extern int func_000B9E08(char *);
extern void func_000B9F18(char *);
extern void func_000BA098(char *);
extern void func_000BA170(char *);

#define F(o) (*(float *)(w + (o)))
#define I(o) (*(int *)(w + (o)))
#define P(o) (*(char **)(w + (o)))

static inline float vecDot(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline int isAxis(float x)
{
    return x < 0.0f ? x < -0x1.6a09e2p-1f : 0x1.6a09e2p-1f < x;
}

static inline int isSide(char *w)
{
    float x = F(0x1F4);
    float d;
    if (x < 0.0f ? x < -0x1.6a09e2p-1f : 0x1.6a09e2p-1f < x)
        return 0;
    d = vecDot(w + 0x1F0, w + 0x130);
    if (d < 0.0f) {
        if (d < -0x1.6a09e2p-1f)
            goto one;
        goto zero;
    }
    if (!(0x1.6a09e2p-1f < d))
        goto zero;
one:
    return 1;
zero:
    return 0;
}

static inline int sideDir(char *w)
{
    if (isSide(w))
    {
        if (!(0.0f <= F(0x1C8))) return 0x1E;
        return 0x1F;
    }
    return 0.0f <= F(0x1C8) ? 0x1D : 0x1C;
}

static inline int pickDir(char *w)
{
    isysGetThisSubThread();
    return func_000B9E08(w);
}

static void func_000BA980(char *w)
{
    int t = isysGetThisSubThread();
    int s;
    int r;
    float rnd;
    float v;

    switch (I(0x15C)) {
    case 3:
        func_000B9948(w);
        s = I(0x164);
        if (s == 1)
            I(0x16C) = 0x1A;
        else if (s == 7)
            I(0x16C) = 0x1A;
        break;
    case 4:
        func_000B9A38(w);
        s = I(0x164);
        if (s == 1)
            I(0x16C) = 0x1A;
        else if (s == 7)
            I(0x16C) = 0x1A;
        else if (s == 3)
            I(0x16C) = 0x1B;
        break;
    case 1:
        func_000B9B00(w);
        s = I(0x164);
        if (s == 2)
            I(0x16C) = func_000B9C98(w);
        else if (s == 4)
            I(0x16C) = 0x1A;
        else if (s == 6)
            I(0x16C) = func_000B9E08(w);
        else if (s == 7)
            I(0x16C) = 0x1A;
        else if (s == 8)
            I(0x16C) = sideDir(w);
        else if (s == 9)
            I(0x16C) = sideDir(w);
        else if (s == 10)
            I(0x16C) = 0x1C;
        else
            I(0x16C) = 0x1A;
        break;
    case 2:
        func_000B9798(w);
        { char *d = P(0x64); float z = 0.0f; __asm__("" : "+f"(z)); AI_UpdateVelocity(w + 0x26C, z, *(float *)(d + 0x5C)); }
        s = I(0x164);
        if (s == 1)
            I(0x16C) = 0x1A;
        else if (s == 6)
            I(0x16C) = func_000B9E08(w);
        else if (s == 7)
            I(0x16C) = 0x1A;
        else if (s == 8)
            I(0x16C) = sideDir(w);
        break;
    case 6:
        r = pickDir(w);
        I(0x16C) = r;
        if (r == 0x1C)
            I(0x170) = 0x15;
        else if (r == 0x1D)
            I(0x170) = 0x16;
        else if (r == 0x1E)
            I(0x170) = 0x17;
        else if (r == 0x1F)
            I(0x170) = 0x18;
        func_000B9798(w);
        AI_UpdateVelocity(w + 0x26C, 0.0f, *(float *)(P(0x64) + 0x5C));
        s = I(0x164);
        if (s == 1)
            I(0x16C) = 0x1A;
        else if (s == 7)
            I(0x16C) = 0x1A;
        break;
    case 7:
        if (I(0x2F4) != 0) {
            rnd = iosGetRandom();
            isysGetThisSubThread();
            if (F(0x190) < F(0x194)) {
                if (rnd < 0.5f) I(0x170) = 0x11; else if (rnd < 1.0f) I(0x170) = 0x12; else I(0x170) = 0x10;
                __asm__("" ::: "memory");
                I(0x194) = 0;
                F(0x190) = 2.0f;
            }
        } else {
            if (0.0f <= F(0x88)) I(0x170) = 0x12; else I(0x170) = 0x11;
        }
        func_000B91C0(w, *(float *)(P(0x64) + 0x44), 1.0f);
        v = *(float *)(P(0x64) + 0x1C);
        F(0x260) = v;
        func_000B9548(w, v, w + 0x210, F(0x23C));
        s = I(0x164);
        if (s == 1)
            I(0x16C) = 0x1A;
        else if (s == 6)
            I(0x16C) = func_000B9E08(w);
        else if (s == 8)
            I(0x16C) = sideDir(w);
        else if (s == 9)
            I(0x16C) = sideDir(w);
        else if (s == 10)
            I(0x16C) = 0x1C;
        break;
    case 8:
        func_000B9F18(w);
        if (I(0x164) == 1)
            I(0x16C) = 0x1A;
        break;
    case 9:
        func_000B9F18(w);
        if (I(0x164) == 1)
            I(0x16C) = 0x1A;
        break;
    case 10:
        func_000B9798(w);
        func_000B93F0(w, I(0x174), I(0x170));
        if (I(0x164) == 12)
            I(0x16C) = 0x1A;
        break;
    case 12: {
        char *d = P(0x64);
        AI_GetRandomVelocity((float *)(w + 0x260), w + 0x198, w + 0x19C,
                             *(float *)(d + 0x18), *(float *)(d + 0x1C), 1.0f, *(float *)(d + 0x48));
        func_000B9548(w, F(0x260), w + 0x210, F(0x23C));
        s = I(0x164);
        if (s == 11)
            I(0x16C) = 0x1C;
        else if (s == 13)
            I(0x16C) = 0x1E;
        break;
    }
    case 11: {
        float tt;
        float *p;
        func_000B9798(w);
        tt = F(0x18C);
        p = (float *)(w + 0x26C);
        if (tt <= F(0x188))
            *p = F(0x2AC) + F(0x2A4) * 0x1.555554p-3f * tt * tt * tt + F(0x2A8) * 0.5f * tt * tt;
        else
            { char *d = P(0x64); float z = 0.0f; __asm__("" : "+f"(z)); AI_UpdateVelocity(p, z, *(float *)(d + 0x5C)); }
        if (I(0x164) == 1)
            I(0x16C) = 0x1A;
        break;
    }
    case 13:
        func_000B9798(w);
        if (I(0x164) == 12)
            I(0x16C) = 0x1A;
        break;
    case 14:
        func_000BA098(w);
        I(0x16C) = 0x20;
        break;
    case 15:
        func_000BA170(w);
        I(0x16C) = 0x20;
        break;
    }

    switch (I(0x16C)) {
    case 27:
        CharaCtrlSetScriptCtrlStatus(t, ScriptCtrlDef_SCRStop->status);
        break;
    case 26:
        CharaCtrlSetScriptCtrlStatus(t, ScriptCtrlDef_SCRGoF->status);
        break;
    case 28:
        CharaCtrlSetScriptCtrlStatus(t, ScriptCtrlDef_SCRGoL->status);
        break;
    case 29:
        CharaCtrlSetScriptCtrlStatus(t, ScriptCtrlDef_SCRGoR->status);
        break;
    case 30:
        CharaCtrlSetScriptCtrlStatus(t, ScriptCtrlDef_SCRFastL->status);
        break;
    case 31:
        CharaCtrlSetScriptCtrlStatus(t, ScriptCtrlDef_SCRFastR->status);
        break;
    case 32:
        CharaCtrlSetScriptCtrlStatus(t, ScriptCtrlDef_SCRDeath->status);
        break;
    }
}
#endif
