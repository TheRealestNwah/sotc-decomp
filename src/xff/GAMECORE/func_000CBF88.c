/* Parked attempt: 6 words differ from the Original. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));
typedef struct { Vec4 p[5]; } PtList;
typedef union { Vec4 v; s128 q; } U4;

extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void iosRotMatrixY(void *, float);
extern Vec4 ZDirVector;
extern int DldSysUndefSymbol;
extern int CheckCollisionInsideOfSurfaceXZ(void *, void *, void *);
extern int widePathCollisionDirect(void *, void *, void *, float, int, int, int);
extern void execPointListSort(char *, void *, void *);
extern int getNearPoint(char *, int, int *, int *, void *, void *, int, int);

static inline void applyMatrix(void *out, void *m, void *v)
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

static inline void scaleVector(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void subXYZW(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(void *v)
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

static inline void quatDir(void *out, void *q)
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

static inline char *dldTarget(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
}

static int func_000CBF88(void *actor, int select, unsigned int *h)
{
    Vec4 dir;
    union { PtList l; s128 q[5]; } ptsU;
#define pts ptsU.l
    Vec4 m[4];
    Vec4 d;
    Vec4 f;
    long long col;
    int n0;
    int n1;
    char *ai;
    char *ctl;
    char *lay;
    char *s;
    int i;

    ai = GetSCRCharaAIWorkPtr(actor);
    ctl = getSCRDataCtrlWork(actor);
    lay = GetLayoutClass(actor);
    iosRotMatrixY(m, (float)*(unsigned int *)(ai + 0x5ACC) * 0.19634954f);
    applyMatrix(&dir, m, &ZDirVector);
    *(s128 *)(ai + 0x5B20) = *(s128 *)&dir;
    ptsU.q[2] = **(s128 **)(*(char **)(ctl + 0x407C) + 0x134);
    pts.p[2].y = 22.5f;
    scaleVector(&pts.p[0], &dir, -*(float *)(ai + 0x5AB0));
    addXYZ(&pts.p[0], &pts.p[0], &pts.p[2]);
    pts.p[0].y = *(float *)(ai + 0x5AB8);
    pts.p[0].w = 1.0f;
    scaleVector(&pts.p[1], &dir, -*(float *)(ai + 0x5AB4));
    addXYZ(&pts.p[1], &pts.p[1], &pts.p[2]);
    pts.p[1].y = *(float *)(ai + 0x5ABC);
    pts.p[1].w = 1.0f;
    scaleVector(&pts.p[3], &dir, *(float *)(ai + 0x5AC4));
    addXYZ(&pts.p[3], &pts.p[3], &pts.p[2]);
    pts.p[3].y = *(float *)(ai + 0x5AC0);
    pts.p[3].w = 1.0f;
    scaleVector(&pts.p[4], &dir, *(float *)(ai + 0x5AC8));
    addXYZ(&pts.p[4], &pts.p[4], &pts.p[2]);
    pts.p[4].y = *(float *)(ai + 0x5ABC);
    pts.p[4].w = 1.0f;
    if (select != 0) {
        *(PtList *)(ai + 0x5AD0) = pts;
        subXYZW(&d, &pts.p[0], *(void **)(lay + 0x134));
        d.y = 0.0f;
        vecNormalize(&d);
        if (vecDot(&dir, &d) < -0.93969262f)
            return 0;
        quatDir(&f, *(void **)(lay + 0x13C));
        f.y = 0.0f;
        vecNormalize(&f);
        if (distanceXZ(&pts.p[0], *(void **)(lay + 0x134)) < 20.0f) {
            if (vecDot(&dir, &f) < -0.93969262f)
                return 0;
            if (vecDot(&d, &f) < -0.93969262f)
                return 0;
        }
    }
    s = dldTarget(h);
    i = 0;
    if (s != 0 && *(void **)(s + 8) != 0 && CheckCollisionInsideOfSurfaceXZ(&col, *(void **)(s + 8), &pts) != 0)
        return 0;
    for (i = 0; i < 4; i++) {
        if (widePathCollisionDirect(ai + 0x10, &pts.p[i], &pts.p[i + 1], *(float *)(ai + 0x3C4C), *(int *)(ai + 0x3C50), 1, 1) != 0)
            return 0;
    }
    execPointListSort(ctl, ctl + 0x2038, &pts);
    if (getNearPoint(ctl, 0, &n0, &n1, ctl + 0x2038, &pts, 1, 1) == 0)
        return 0;
    if (select != 0)
        return 1;
    *(PtList *)(ai + 0x5AD0) = pts;
    return 1;
}
#endif
