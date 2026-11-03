typedef float Vec4[4] __attribute__((aligned(16)));
typedef int s128 __attribute__((mode(TI)));

typedef union { float f; int i; } FI;
typedef struct {
    char pad0[8];
    char *frames;
} IKAnim;

typedef struct {
    void *obj;
    char *quats;
    char pad8[8];
    IKAnim *anim;
    int node;
    unsigned int *h;
} IKLeg;

extern Vec4 B_0018A4F0;
extern float B_0018A530;
extern Vec4 ZUnitVector;
extern int *DldSysUndefSymbol;
extern Vec4 B_0018A540;
extern Vec4 B_0018A550;
extern s128 ZeroPoint;
extern Vec4 ZUnitVectorInv;
extern Vec4 YUnitVector;
extern Vec4 IdentityQuaternion;
extern float iosGetATan2fExact(float, float);
extern void RotQuaternionXExact(float *, float *, float);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);
extern char *GetLayoutClass(void *);
extern void *GetCharacterClass(void *);
extern void GetCharacterClassOptionNodeLocalQuaternionPos(float *, float *, void *, int, int);

static inline void vecMulXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatPosApply(float *out, float *quat, float *pos, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%3)\n"
                         "lqc2 vf18, 0x0(%2)\n"
                         "vmove.w vf18, vf0\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf18, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(quat), "r"(pos), "r"(v) : "memory");
}

static inline void getAddSubPosition(float *out, IKLeg *leg, float *v)
{
    Vec4 tmp;
    Vec4 pos;
    void *obj = leg->obj;
    char *layout = GetLayoutClass(obj);
    int node = leg->node;

    if (node > 0 && (node & 0x10000)) {
        int n = node & ~0x10000;
        GetCharacterClassOptionNodeLocalQuaternionPos(tmp, out, GetCharacterClass(obj), n, 0);
        return;
    }
    vecMulXYZ(pos, (float *)(leg->anim->frames + node * 0x40 + 0x10), (float *)(layout + 0x90));
    quatPosApply(out, (float *)(leg->quats + leg->node * 0x10), pos, v);
}

static inline void quatFwdAxis(float *out, float *q)
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

static inline void quatMul(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(float *out, float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v) : "memory");
}

static inline void quatZero(float *out)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(out) : "memory");
}

static inline void quatConj(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

typedef struct {
    char pad0[0x320];
    FI *f320;
    FI *f324;
    s128 *q328;
} CC;

void nico_IK_legSetLower(IKLeg *leg)
{
    Vec4 rot;
    Vec4 dq;
    Vec4 inv;
    Vec4 axis;
    float *base;
    char *cc;
    char *d;

    base = (float *)(leg->anim->frames + leg->node * 0x40 + 0x20);
    RotQuaternionXExact(rot, IdentityQuaternion, -B_0018A530);
    quatMul(rot, rot, B_0018A540);
    quatConj(inv, base);
    quatMul(inv, inv, rot);
    quatFwdAxis(axis, inv);
    GetDifferencialQuaternionWithNoRegularize(dq, axis, ZUnitVector, YUnitVector);
    quatMul(((Vec4 *)leg->quats)[leg->node], base, dq);
    quatMul(((Vec4 *)leg->quats)[leg->node], ((Vec4 *)leg->quats)[leg->node], B_0018A550);
    cc = GetCharacterClass(leg->obj);
    d = dldResolve(leg->h);
    ((CC *)cc)->f324[leg->node].f = *(float *)(d + 0x1C);
    ((CC *)cc)->f320[leg->node].f = 1.0f;
    ((CC *)cc)->q328[leg->node] = *(s128 *)((Vec4 *)leg->quats)[leg->node];
}
