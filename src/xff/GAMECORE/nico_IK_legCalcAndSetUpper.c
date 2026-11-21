/* Two-bone IK for the upper leg: law-of-cosines angles from the three segment lengths, then aims the base quaternion at the target and applies Z/X rotations. Union stores keep leg->node reloaded after each float store as in the Original. The register pins on the vecScale/quatRotate operands and the "+r" on the rotate output reproduce the Original's register choice and the recomputed sp+0x30 address. */
typedef float Vec4[4] __attribute__((aligned(16)));
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    void *obj;
    char *quats;
    char *frames;
    char *baseQuats;
    char pad10[4];
    int node;
    unsigned int *handle;
    char pad1C[4];
    Vec4 dir;
} IKLeg;

extern int DldSysUndefSymbol;
extern Vec4 B_0018A4E0;
extern float B_0018A500;
extern Vec4 B_0018A510;
extern Vec4 B_0018A520;
extern float B_0018A530;
extern Vec4 ZUnitVector;
extern char *GetCharacterClass(void *);
extern float iosGetACosfExact(float);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);
extern void RotQuaternionZExact(float *, float *, float);
extern void RotQuaternionXExact(float *, float *, float);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline float lenSq(float *v)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(v) : "$2");
    return d;
}

static inline float fsqrt(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatUpAxis(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void vecScale(float *out, float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(s) : "memory");
}

static inline void quatConj(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void quatRotate(float *out, float *quat, float *v)
{
    register float *o __asm__("$2") = out;
    register float *vv __asm__("$5") = v;
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
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
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : "+r"(o) : "r"(quat), "r"(vv) : "memory");
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

static inline void quatNormalize(float *q)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(q) : "memory");
}

void nico_IK_legCalcAndSetUpper(IKLeg *leg)
{
    Vec4 d;
    Vec4 up;
    Vec4 dn;
    Vec4 r;
    Vec4 inv;
    Vec4 dq;
    char *e;
    char *e2;
    char *cc;
    float sq1, sq2, sq3;
    float l1, l2, l3;
    float a, b;

    e = dldResolve(leg->handle);
    sq1 = lenSq(B_0018A520);
    l1 = fsqrt(sq1);
    sq2 = lenSq(B_0018A510);
    l2 = fsqrt(sq2);
    vecSubXYZ(d, B_0018A4E0, (float *)(leg->frames + leg->node * 0x40 + 0x30));
    sq3 = lenSq(d);
    l3 = fsqrt(sq3);
    if (l3 < l1 + l2) {
        a = iosGetACosfExact((sq3 + sq2 - sq1) / (2.0f * l3 * l2));
        b = iosGetACosfExact((sq3 + sq1 - sq2) / (2.0f * l3 * l1));
        B_0018A530 = b + a;
        if (*(int *)(e + 0x24) != 0) {
            b = -b;
            B_0018A530 = -B_0018A530;
        }
    } else {
        { float z = 0.0f; B_0018A530 = z; b = z; }
    }
    cc = GetCharacterClass(leg->obj);
    quatUpAxis(up, *(float **)(cc + 0x13C));
    vecScale(dn, d, -1.0f / l3);
    quatConj(inv, (float *)(leg->baseQuats + leg->node * 0x10));
    quatRotate(r, inv, dn);
    GetDifferencialQuaternionWithNoRegularize(dq, r, ZUnitVector, leg->dir);
    quatMul((float *)(leg->quats + leg->node * 0x10), (float *)(leg->quats + leg->node * 0x10), dq);
    RotQuaternionZExact((float *)(leg->quats + leg->node * 0x10), (float *)(leg->quats + leg->node * 0x10), B_0018A500 * (1.0f - *(float *)(e + 0x2C) * 0.01f));
    RotQuaternionXExact((float *)(leg->quats + leg->node * 0x10), (float *)(leg->quats + leg->node * 0x10), b);
    quatNormalize((float *)(leg->quats + leg->node * 0x10));
    cc = GetCharacterClass(leg->obj);
    e2 = dldResolve(leg->handle);
    {
        typedef union { float f; int i; } U;
        ((U *)*(char **)(cc + 0x324))[leg->node].f = *(float *)(e2 + 0x1C);
        ((U *)*(char **)(cc + 0x320))[leg->node].f = 1.0f;
    }
    *(s128 *)(*(char **)(cc + 0x328) + leg->node * 0x10) = *(s128 *)(leg->quats + leg->node * 0x10);
}
