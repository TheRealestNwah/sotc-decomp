typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    int id;
    void *ptn;
    int a;
    int b;
    int c;
    int d;
    int e;
    int func;
    int f;
    int g;
    int h;
} LWSSetup;

typedef struct {
    char pad[0x180];
    float a;
    float b;
} GVar;

extern GVar gcGlobalVar;
extern char rootPtn[];
extern void *CreateScriptAnimationSequence(LWSSetup *);
extern void PlayScriptAnimationSequence(void *, int, int, int);
extern void *get_main_cameraman_camera_obj(void);
extern void ExecObjectAnimation(void *, void *, float, float);
extern char ZeroPoint[];
extern char *GetDamageClass(int);
extern float *GetGeometryPointerSurfacePlane(void *);
extern void iosGetArbitraryUpVectorElement(float *, float *);
extern void GetQuaternionByAxisDirZY(float *, float *, float *);
extern void GetGeometryPointerQuaternion(float *, void *);
#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory")
static inline void quatConj(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

void *_SCRPlayLWSWithTargetAttackedPoint(int id, int target)
{
    Vec4 up;
    Vec4 dq;
    Vec4 gq;
    Vec4 q;
    LWSSetup s;
    char *geo;
    float *plane;
    char *zp;
    void *o;

    geo = GetDamageClass(target) + 0x10;
    plane = GetGeometryPointerSurfacePlane(geo);
    iosGetArbitraryUpVectorElement(up, plane);
    GetQuaternionByAxisDirZY(dq, up, plane);
    GetGeometryPointerQuaternion(gq, geo);
    quatConj(gq, gq);
    VU_QUAT_MUL(q, gq, dq);
    zp = ZeroPoint;
    s.id = id;
    s.ptn = rootPtn;
    s.a = (int)geo;
    s.b = (int)zp;
    s.c = (int)q;
    s.e = target;
    s.g = 1;
    s.h = -1;
    s.d = 0;
    s.func = 0;
    s.f = 0;
    o = CreateScriptAnimationSequence(&s);
    if (o != 0) {
        PlayScriptAnimationSequence(o, 0, -1, 3);
        ExecObjectAnimation(o, get_main_cameraman_camera_obj(), gcGlobalVar.a, gcGlobalVar.b);
    }
    return o;
}
