/* func_000A5260: Parked attempt, 17 diffs, same size.
 * The 0.1f constant is CSE'd into $f20 and reused across the three calls,
 * where the Original rematerializes lui/ori/mtc1 before each one; the
 * memory barrier also makes p+0x2F8 reload instead of reusing $f0.
 */
#ifdef NONMATCHING
typedef struct { char pad[0x190]; float dt; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern void *isysGetThisSubThread(void);
extern float iosGetACosfExact(float);
extern float iosGetASinfExact(float);
extern int AI_GetSideSignalFromDirLev(void *, void *);
extern float AI_GetRotVelocity(float, float, float, float);
extern void AI_GetTrgDir(float *, float *, float);
extern void AI_UpdateVelocity(float *, float, float);
extern float iosGetTableSin(short);
extern float iosGetTableCos(short);

#define F(p, o) (*(float *)((char *)(p) + (o)))

static inline float vecDot(void *a, void *b)
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

static inline float vecLength(void *a)
{
    float len;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(a) : "$2");
    return len;
}

static void func_000A5260(char *p, char *trg)
{
    float dir[4];
    float rot, d, ang, a, len, v, spd, r, k, sn;
    char *o, *o2;
    float *s3, *ry, *rv, *u1, *u2;
    float w, k2;

    isysGetThisSubThread();
    rot = F(*(char **)(p + 0x20), 0xB4);
    d = vecDot(trg + 0x30, p + 0x240);
    ang = iosGetACosfExact(d);
    ang = ang * (float)AI_GetSideSignalFromDirLev(p + 0x240, trg + 0x30);
    w = 1.0f - (d + 1.0f) * 0.5f;
    F(p, 0x2F0) = d;
    F(p, 0x2F4) = AI_GetRotVelocity(F(p, 0x2F4) * 90.0f * 3.1415926f / 180.0f, ang, rot, 0.1f) * 180.0f / 282.74332f;
    k = F(*(char **)(p + 0x20), 0xE0);
    if (F(trg, 0x48) < 0.0f)
        k = 0.0f;
    AI_GetTrgDir(dir, (float *)trg, k);
    ry = (float *)(p + 0x304);
    rv = (float *)(p + 0x2FC);
    a = iosGetASinfExact(dir[1]) + 0.0f;
    if (a > 1.5707963f)
        a = 1.5707963f;
    else if (a < -1.5707963f)
        a = -1.5707963f;
    F(p, 0x300) = a;
    F(p, 0x2F8) = AI_GetRotVelocity(F(p, 0x2F8), a - *ry, 3.0f, 0.1f);
    __asm__ __volatile__("" ::: "memory");
    *ry = *ry + F(p, 0x2F8) * gcGlobalVar.dt;
    AI_UpdateVelocity(rv, *ry, 0.1f);
    o = *(char **)(p + 0x20);
    s3 = (float *)(o + 0x70);
    len = vecLength(p + 0x2E0);
    v = -len * F(o, 0x20);
    if (F(p, 0x2E8) < 0.0f)
        v = -v;
    sn = iosGetTableSin((short)(int)(F(p, 0x300) * 32768.0f / 3.1415926f));
    o2 = *(char **)(p + 0x20);
    spd = len + ((s3[2] * (F(p, 0x314) - F(p, 0x318)) + -F(o2, 0x24) * F(o2, 0x1C) * sn * s3[1] + v) / F(o2, 0x1C)) * gcGlobalVar.dt;
    F(p, 0x2E4) = spd * iosGetTableSin((short)(int)(F(p, 0x304) * 32768.0f / 3.1415926f));
    F(p, 0x2E8) = spd * iosGetTableCos((short)(int)(F(p, 0x304) * 32768.0f / 3.1415926f));
    k2 = F(*(char **)(p + 0x20), 0x70);
    u1 = (float *)(p + 0x314);
    u2 = (float *)(p + 0x318);
    AI_UpdateVelocity(u1, F(p, 0x300) / 1.5707963f + 1.0f, 1.0f);
    { float m = F(p, 0x7E8); r = spd / (F(*(char **)(p + 0x20), 0x28) * m); }
    AI_UpdateVelocity(u2, w * (r * r) * k2, 2.0f);
    F(p, 0x30C) = *u1 + *u2 + 0.0f;
}
#endif
