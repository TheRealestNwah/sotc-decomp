typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct { char pad[0x190]; float delta; } GlobalVar;
extern GlobalVar gcGlobalVar;
extern void AI_GetRandomVelocity(void *, void *, void *, float, float, float, float);
extern float AI_GetRotVelocity(float, float, float, float);
extern int AI_GetSideSignalFromDirLev(void *, void *);
extern void AI_UpdateVelocity(void *, float, float);
extern char *GetLayoutClass(void *);
extern void *isysGetThisSubThread(void);
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

static void func_000A4D58(char *w, char *p)
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
    off = *(float *)(k2 + 0x90) * 0.017453293f;
    mul = *(float *)(k2 + 0x94);
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
    q = k + 0x50;
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
    r = *(float *)(*(char **)(w + 0x20) + 0x50);
    AI_UpdateVelocity(w + 0x314, u + *(float *)(w + 0x300) / 1.5707963f, 2.0f);
    {
        register float lim __asm__("$f1") = *(float *)(w + 0x7E8);
        spd = spd / (*(float *)(*(char **)(w + 0x20) + 0x28) * lim);
    }
    AI_UpdateVelocity(w + 0x318, base * (spd * spd) * r, 2.0f);
    *(float *)(w + 0x30C) = *(float *)(w + 0x314) + *(float *)(w + 0x318) + zero;
    *(float *)(w + 0x310) = 1.0f;
}
