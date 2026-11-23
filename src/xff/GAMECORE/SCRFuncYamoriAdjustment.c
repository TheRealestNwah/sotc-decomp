/*
 * Steers a Yamori-type character toward a fixed point (-965, -69.5, 950)
 * while its current animation is the one resolved from the Dld handle. */

typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { u_long128 q; Vec4 f; } VecQ;

extern char *GetLayoutClass(void *);
extern int *GetAnimationClass(void *);
extern float iosGetATan2fExact(float, float);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void SCRCharaTurnDirectInput(void *, float);
extern int *ScriptCtrlDef_SCRGoR;
extern int *ScriptCtrlDef_SCRGoL;
extern char *DldSysUndefSymbol;
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V4;

static inline void quatDir(float *dst, float *q)
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
                         : : "r"(dst), "r"(q) : "memory");
}

static inline void vecNormalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void vecSub(float *d, float *a, float *b)
{
    register float *dd __asm__("$2") = d;
    register float *bb __asm__("$3") = b;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dd), "r"(a), "r"(bb) : "memory");
}

static inline void vecZero(float *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
}

static inline void vecZeroNC(float *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(v));
}

static inline float vecDot(float *a, float *b)
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

static inline void quatToMatrix(float *out, float *quat)
{
    register float *o __asm__("$3") = out;
    register float *qq __asm__("$2") = quat;
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(o), "r"(qq) : "memory");
}

static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void matApply(float *out, float *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                         : : "r"(v), "r"(m), "r"(out) : "memory");
}

static inline char *resolve(unsigned int *h)
{
    unsigned int v = *h;
    char *t;
    if (v & 0x3FFFF)
        t = *(char **)((char *)h - (v & 0x3FFFF));
    else
        t = 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC);
    return 0;
}

void SCRFuncYamoriAdjustment(void *obj, float f, int a1, int a2, int a3, int t0, int t1, unsigned int *h)
{
    V4 tgt = { -965.0f, -69.5f, 950.0f, 1.0f };
    char *lay;
    int *anim;
    VecQ to, A, B, dir, sel;
    Vec4 m[4];
    float s, b, len, a, v;

    lay = GetLayoutClass(obj);
    anim = GetAnimationClass(obj);
    if (*anim != (int)resolve(h))
        return;
    quatDir(dir.f, *(float **)(lay + 0x13C));
    dir.f[1] = 0.0f;
    vecNormalize(dir.f);
    { float *p = *(float **)(lay + 0x134); vecSub(to.f, (float *)&tgt, p); }
    to.f[1] = 0.0f;
    vecNormalize(to.f);
    vecZero(A.f);
    vecZero(B.f);
    B.f[0] = to.f[2];
    A.f[2] = to.f[0];
    A.f[0] = -to.f[2];
    B.f[2] = -to.f[0];
    if (vecDot(dir.f, A.f) > vecDot(dir.f, B.f))
        sel.q = A.q;
    else
        sel.q = B.q;
    s = *(float *)((char *)anim + 0x2C);
    b = *(float *)((char *)anim + 8) * s;
    len = ((f - b) * s) / (float)*(int *)(*(char **)anim + 0x5C);
    if (f < b)
        return;
    quatToMatrix(m[0], *(float **)(lay + 0x13C));
    vecZeroNC(m[3]);
    matInverse(m[0], m[0]);
    matApply(sel.f, m[0], sel.f);
    a = iosGetATan2fExact(sel.f[0], sel.f[2]);
    if (!(__builtin_fabsf(a) > 0.017453293f))
        return;
    v = (a / len) / ((float)*(int *)(*(char **)anim + 0x74) * 0.017453293f);
    if (v > 1.0f)
        v = 1.0f;
    else if (v < -1.0f)
        v = -1.0f;
    if (a > 0.0f) {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRGoR[1]);
        SCRCharaTurnDirectInput(obj, v);
    } else {
        CharaCtrlSetScriptCtrlStatus(obj, ScriptCtrlDef_SCRGoL[1]);
        SCRCharaTurnDirectInput(obj, v);
    }
}

