typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

typedef int s128 __attribute__((mode(TI)));
typedef struct { long long x, y; } Pair;

extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int getNearPointPosUserPathWork(void *, void *, void *, int, int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern s128 *GetGeometryPointerSurfacePlane(void *);
extern void setAttainmentPosAndDir(void *, void *, void *);
extern int func_0006BC58(void *);
extern long GetGeometryPointerCharColAttr(void *);

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

static inline void vecScale(void *out, void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(v), "r"(s), "r"(out) : "memory");
}

static inline void vecAdd(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(out) : "memory");
}

#ifdef NONMATCHING
/* Parked: 77 words differ (callee-saved float register order for a/b/c, and block layout of the attribute switch). */
void SCRFuncMinoCSetTemporaryTarget(void *obj, int u1, int u2, long long ex, long long ey, float a, float b, float c)
{
    char buf[0x50];
    Pair held;
    char pt[0x10] __attribute__((aligned(16)));
    struct { Vec4 v80; Vec4 nrm; Vec4 vA0; Vec4 vB0; } L;
    char *work;
    char *attain;
    char *ctrl;
    char *grp;
    float scale;

    work = GetSCRCharaAIWorkPtr(obj);
    ctrl = getSCRDataCtrlWork(obj);
    attain = work + 0x10;
    *(s128 *)&L.v80 = **(s128 **)(*(char **)(ctrl + 0x407C) + 0x134);
    held.x = ex;
    held.y = ey;
    getNearPointPosUserPathWork(attain, pt, &L.v80, 1, -1);
    grp = gcGlobalVar + 0x238;
    if (ClipCollisionDirectCallBack(buf, pt, &L.v80, grp, 0, 0, 0, func_0006BC58, &held) == 0)
        goto fail;
    *(volatile s128 *)&L.nrm = *GetGeometryPointerSurfacePlane(buf);
    *(volatile float *)&L.nrm.y = 0.0f;
    vecNormalize(&L.nrm);
    vecScale(&L.vA0, &L.nrm, 30.0f);
    vecAdd(&L.vA0, &L.v80, &L.vA0);
    L.vA0.w = 1.0f;
    if (ClipCollisionDirectCallBack(buf, &L.vA0, &L.v80, grp, 0, 0, 0, func_0006BC58, &held) == 0)
        goto fail;
    *(volatile s128 *)&L.nrm = *GetGeometryPointerSurfacePlane(buf);
    *(volatile float *)&L.nrm.y = 0.0f;
    vecNormalize(&L.nrm);
    {
        long long attr = GetGeometryPointerCharColAttr(buf);
        if ((attr & 0x3F800000000000LL) == 0x2000000000000LL)
            scale = c;
        else if ((attr & 0x3F800000000000LL) == 0x1800000000000LL)
            scale = b;
        else
            goto weak;
        vecScale(&L.vA0, &L.nrm, scale);
        if (*(int *)(work + 0x41FC) != 2) {
            *(int *)(work + 0x41FC) = 2;
            if (*(int *)(work + 0x41F8) == 0)
                *(int *)(work + 0x41F8) = 1;
        }
        goto done;
    weak:
        vecScale(&L.vA0, &L.nrm, a);
        if (*(int *)(work + 0x41FC) != 1) {
            *(int *)(work + 0x41FC) = 1;
            if (*(int *)(work + 0x41F8) == 0)
                *(int *)(work + 0x41F8) = 1;
        }
    done:;
    }
    vecAdd(&L.vA0, buf + 0x40, &L.vA0);
    L.vA0.w = 1.0f;
    vecScale(&L.vB0, &L.nrm, -1.0f);
    L.vB0.w = 1.0f;
    setAttainmentPosAndDir(attain, &L.vA0, &L.vB0);
    *(int *)(work + 0x41F0) = 1;
    return;
fail:
    *(int *)(work + 0x41F0) = 0;
}
#else
void SCRFuncMinoCSetTemporaryTarget(void *obj, int u1, int u2, long long ex, long long ey, float a, float b, float c);
#endif
