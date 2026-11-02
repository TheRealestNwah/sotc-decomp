typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern int ScriptLayoutObjDef_MINOTAUR_WEAPON;
extern char gcGlobalVar[];
extern char ZeroPoint[], IdentityQuaternion[], XUnitVector[];
typedef struct { int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o; } MParam;
extern void *initScriptLayoutObj(Ptn *, int, MParam *, int, int, void *, int);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern void SetGeometryPointerNodePosState(void *, void *, int, void *, void *);
extern void GetMotionNodeQuaternionPosToolCoord(float *, float *, void *, int, int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);

#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory")

static inline void quatMul(float *d, float *a, float *b)
{
    VU_QUAT_MUL(d, a, b);
}

static inline void rotQuatX(float *d, float *a)
{
    float r[4] __attribute__((aligned(16)));

    SetQuaternionByAxisRotateVWithNoRegularize(r, -0x8000, XUnitVector);
    quatMul(d, a, r);
}

void *SCRSetupWeaponMinotaur(void *obj)
{
    float q[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    char geo[0x40] __attribute__((aligned(16)));
    void *o;

    SetGeometryPointerNodePosState(geo, obj, 0x10000, IdentityQuaternion, ZeroPoint);
    GetMotionNodeQuaternionPosToolCoord(q, pos, obj, 0x10000, 0);
    rotQuatX(q, q);
    {
        MParam s;

        s.a = 0;
        s.b = (int)ZeroPoint;
        s.c = (int)IdentityQuaternion;
        s.d = 0;
        s.e = 0;
        s.f = 0;
        s.g = 0;
        s.h = 1;
        s.i = (int)geo;
        s.j = 0;
        s.k = 0;
        s.l = 1;
        s.m = 0;
        s.n = 0;
        s.o = 0;
        o = initScriptLayoutObj(&rootPtn, ScriptLayoutObjDef_MINOTAUR_WEAPON, &s, 0, 4, obj, 0);
    }
    if (o != 0)
        isysAddGroupWithLinkParam(o, gcGlobalVar + 0x280, 0, 0);
    return o;
}
