#include "common.h"
#include "gamecore/perception.h"

extern struct { char pad[0x190]; float dt; } gcGlobalVar;
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int getSoundBowPos(PercWork *, void *);
static inline float distXZ(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2", "memory");
    return d;
}
static inline float distXYZ(void *a, void *b)
{
    float len;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(a), "r"(b) : "$2", "memory");
    return len;
}
#define DT (gcGlobalVar.dt)
/* PercRes and the target layout's position pointer share unions with floats so
 * their loads stay after the preceding float stores, as in the Original. */
union PU { PercVec4 *p; float f; };
/* prm is pinned to s4 and the first quatPosToMatrix call goes through a copy
 * that pins its quat/pos pointers to v1/a1, as in the Original. */
typedef float Vec4_perceptionExec[4] __attribute__((aligned(16)));
typedef union {
    u_long128 q;
    Vec4_perceptionExec f;
} VecQ;
static inline void vecNormalize(float *dst, float *src)
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
                         : : "r"(dst), "r"(src) : "memory");
}
static inline void quatPosToMatrix(float *out, float *quat, float *pos)
{
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
                         : : "r"(out), "r"(quat) );
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(pos) : "memory");
}
/* quatPosToMatrix with its input pointers pinned to v1/a1. */
static inline void quatPosToMatrixP(float *out, float *quat, float *pos)
{
    register float *q_ asm("$3") = quat;
    register float *p_ asm("$5") = pos;
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
                         : : "r"(out), "r"(q_) );
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(p_) : "memory");
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
                         "qmfc2 $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2 $8, vf24\n"
                         "qmtc2 $9, vf25\n"
                         "qmtc2 $10, vf26\n"
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
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}
extern char *GetCharacterClass(void *);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern int SCRGetCollisionCallBack(void *, void *, void *, void *, int (*)(), int);
extern float iosGetATan2fExact(float, float);
extern float ZeroPoint[];
static inline float distanceXZ(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}
static inline float vecLength(void *a)
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
extern void *SCRGetFirstObj(void *);
extern void scrRun(void);
union PerceptionVector {
    s128 q;
    float f[4];
    int words[4];
    void *pointers[4];
};
extern int _omakeSelectFlagChk(int);
extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_00122CB8(void *surface);

void updatePerceptionWork(void *obj)
{
    PercRes res;
    PercWork *w;
    PercParam *p;
    char *lay;
    char *t;

    w = (PercWork *)(getSCRDataCtrlWork(obj) + 0x4030);
    p = w->param;
    lay = GetLayoutClass(obj);
    t = w->targetLay;
    w->distXZ = distXZ(*(void **)(t + 0x134), *(void **)(lay + 0x134));
    w->dist = distXYZ(*(void **)(t + 0x134), *(void **)(lay + 0x134));
    if (w->param == 0) {
        w->lost = 0;
        return;
    }
    ((void (*)(void *, PercWork *, PercRes *, void *))perceptionExec)(obj, w, &res, *(void **)(t + 0x134));
    w->res = res;
    if (((int (*)(void))equipmentInvisibilityCloak)() != 0) {
        w->lostTime = w->lostTime <= 0.0f ? 0.0f : w->lostTime;
    } else {
        if (w->hTime < -p->h)
            w->hTime = -p->h;
        if (w->vTime < -p->v)
            w->vTime = -p->v;
        if (w->lostTime < -p->lost)
            w->lostTime = -p->lost;
    }
    if (res.i.a == 0 && res.i.b == 0) {
        if (getSoundBowPos(w, *(void **)(lay + 0x134))) {
            w->bowTime = p->bow;
            w->lostTime = 0.0f <= w->lostTime ? 0.0f : w->lostTime;
        } else {
            w->bowTime -= DT;
            w->bowTime = w->bowTime <= 0.0f ? 0.0f : w->bowTime;
            if (w->bowTime <= 0.0f)
                w->pos.q = w->last.q;
        }
        w->lostTime += DT;
        if (0.0f < w->lostTime) {
            w->hTime = -p->h;
            w->vTime = -p->v;
        }
    } else {
        if (res.i.a)
            w->hTime += DT;
        if (res.i.b)
            w->vTime += DT;
        if (0.0f < w->hTime || 0.0f < w->vTime) {
            w->lostTime = -p->lost;
            w->pos.q = ((union PU *)(w->targetLay + 0x134))->p->q;
            w->last.q = ((union PU *)(w->targetLay + 0x134))->p->q;
            if (w->vTime <= 0.0f)
                w->vTime = 0.0f;
            else if (w->hTime <= 0.0f)
                w->hTime = 0.0f;
        }
    }
    if (w->lostTime <= 0.0f) {
        w->bowTime = 0.0f;
        w->lost = 1;
    } else {
        w->lost = 0;
    }
}

int perceptionExec(void *obj, char *w, int *res, float *target)
{
    VecQ pos;
    VecQ quat;
    Vec4_perceptionExec inv1[4];
    Vec4_perceptionExec m1[4];
    VecQ d;
    Vec4_perceptionExec inv2[4];
    Vec4_perceptionExec m2[4];
    VecQ lp;
    VecQ dir;
    char out[0x40];
    char *ch = GetCharacterClass(obj);
    char *lay = GetLayoutClass(obj);
    register float *prm asm("$20") = *(float **)(w + 0x40);
    char *bone;
    float v;

    res[1] = 0;
    res[0] = 0;
    if (((int (*)(void))equipmentInvisibilityCloak)() != 0)
        return 0;
    bone = *(char **)(w + 0x44);
    if (bone != 0) {
        GetMotionNodeQuaternionPos(&quat, &pos, obj, *(int *)(bone + 8), 1);
    } else {
        quat.q = *(u_long128 *)(ch + 0x470);
        pos.q = **(u_long128 **)(lay + 0x134);
    }
    quatPosToMatrixP(m1[0], (float *)(ch + 0x470), pos.f);
    matInverse(inv1[0], m1[0]);
    matApply(d.f, inv1[0], target);
    if (distanceXZ(ZeroPoint, d.f) <= prm[0] && __builtin_fabsf(d.f[1]) <= prm[1])
        res[1] = 1;
    quatPosToMatrix(m2[0], quat.f, pos.f);
    matInverse(inv2[0], m2[0]);
    matApply(lp.f, inv2[0], target);
    dir.q = lp.q;
    dir.f[1] = 0;
    vecNormalize(dir.f, dir.f);
    ((float *)res)[2] = iosGetATan2fExact(dir.f[0], dir.f[2]);
    dir.q = lp.q;
    dir.f[0] = 0;
    vecNormalize(dir.f, dir.f);
    ((float *)res)[3] = iosGetATan2fExact(dir.f[1], dir.f[2]);
    if (__builtin_fabsf(((float *)res)[2] * 57.29578f) <= prm[3]) {
        v = ((float *)res)[3] * 57.29578f;
        if (v <= prm[4] && prm[5] <= v && vecLength(lp.f) <= prm[2]
            && SCRGetCollisionCallBack(out, pos.f, target, (char *)&gcGlobalVar + 0x250, func_00122CB8, 0) == 0)
            res[0] = 1;
    }
    if (res[1] != 0 || res[0] != 0)
        return 1;
    return 0;
}

void createPerceptionWork(void *a, int b)
{
    char *w = getSCRDataCtrlWork(a) + 0x4030;
    while ((*(void **)(w + 0x48) = SCRGetFirstObj((char *)&gcGlobalVar + 0x2B0)) == 0)
        scrRun();
    *(char **)(w + 0x4C) = GetLayoutClass(*(void **)(w + 0x48));
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(w) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(w + 0x10) : "memory");
    *(int *)(w + 0x44) = b;
    *(int *)(w + 0x40) = 0;
}

void setPerceptionParam(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x40)) = arg1;
}

int perceptionExec2(void *obj, char *w, void *target)
{
    PercVec4 pos;
    PercVec4 quat;
    char *ch = GetCharacterClass(obj);
    char *lc = GetLayoutClass(obj);
    char *bone;

    if (((int (*)(void))equipmentInvisibilityCloak)() != 0)
        return 0;
    bone = *(char **)(w + 0x44);
    if (bone != 0) {
        GetMotionNodeQuaternionPos(&quat, &pos, obj, *(int *)(bone + 8), 1);
    } else {
        quat.q = *(s128 *)(ch + 0x470);
        pos.q = **(s128 **)(lc + 0x134);
    }
    {
        char out[0x40];

        return SCRGetCollisionCallBack(out, &pos, target, (char *)&gcGlobalVar + 0x250, func_00122CB8, 0) == 0;
    }
}

void forceSetPerceptionWork(void *arg0, void *work)
{
    void *context = *(void **)((char *)work + 0x40);

    if (context != 0) {
        void *actor = *(void **)((char *)work + 0x4C);
        float negative;

        ((volatile union PerceptionVector *)work)->q = (*(union PerceptionVector **)((char *)actor + 0x134))->q;
        ((volatile union PerceptionVector *)((char *)work + 0x10))->q = (*(union PerceptionVector **)((char *)actor + 0x134))->q;
        negative = -*(volatile float *)((char *)context + 0x18);
        *(volatile int *)((char *)work + 0x20) = 0;
        *(volatile int *)((char *)work + 0x24) = 0;
        *(volatile float *)((char *)work + 0x28) = negative;
    }
}

void forceRenewLastPosPerceptionWork(void *unused, PerceptionWork *work)
{
    PerceptionObj *obj = work->obj;

    work->last[0] = *obj->pos.pos;
    work->last[1] = *obj->pos.pos;
}

int equipmentInvisibilityCloak(int a, int b, int c, int d)
{
    return _omakeSelectFlagChk(7);
}

static int func_00122CB8(void *surface)
{
    unsigned long attribute;
    unsigned long kind, mode, flags;

    attribute = *GetCollisionDBAttributeAdr(surface);
    flags = attribute & (0xF800UL << 20);
    kind = attribute & 0x7C000000;
    mode = attribute & (0xF000UL << 30);
    if (flags == (0x8000UL << 18) || flags == (0xB800UL << 20) || flags == (0xC000UL << 18) || flags == (0xA000UL << 19) ||
        flags == (0xA000UL << 18) || kind == 0x04000000 || kind == 0x64000000 || kind == 0x68000000 ||
        kind == 0x6C000000)
        return 0;
    if (kind == 0x24000000 || flags == (0xE000UL << 18) || mode == (0x8000UL << 28))
        return 0;
    return 1;
}
