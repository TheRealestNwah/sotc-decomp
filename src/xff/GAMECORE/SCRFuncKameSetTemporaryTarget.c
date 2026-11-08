typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

typedef struct { long long a, b; } LL2;
typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirect(void *, void *, void *, void *);
extern void *getPlayerColCont2(void *);
extern int ColCont2_IsColStatus(void *, long long, long long);
extern void setAttainmentPos(void *, void *);
extern long long RO_00180AD0[];
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern s128 *GetGeometryPointerSurfacePlane(void *);
extern void setAttainmentPosAndDir(void *, void *, void *);

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
/* Flag note: 12 diffs with per-file -fno-strict-aliasing (19 without); permuter with the flag found no improvement. */
/* Parked: 19 words differ (RO copy scheduled before the ctrl call; lui s7 order; one swc1/lq swap). */
void SCRFuncKameSetTemporaryTarget(void *obj, float a, float b)
{
    struct { char buf[0x50]; Vec4 p50; Vec4 v60; Vec4 o70; Vec4 n80; } L;
    int retry = 0;
    Vec4 *pp50;
    Vec4 *pv60;
    Vec4 *pn80;
    Vec4 *po70;
    char *pb40;
    float one;
    char *work;
    char *ctrl;

    work = GetSCRCharaAIWorkPtr(obj);
    *(LL2 *)&L.p50 = *(LL2 *)RO_00180AD0;
    ctrl = getSCRDataCtrlWork(obj);
    *(s128 *)&L.v60 = **(s128 **)(*(char **)(ctrl + 0x407C) + 0x134);
    if (ColCont2_IsColStatus(getPlayerColCont2(*(void **)(ctrl + 0x4078)), 0xFE00LL << 38, 0xB000LL << 36) != 0) {
        L.p50.x = 818.0f;
        L.p50.y = 21.0f;
        L.p50.z = -1045.0f;
    }
    one = 1.0f;
    pp50 = &L.p50;
    pv60 = &L.v60;
    pn80 = &L.n80;
    po70 = &L.o70;
    pb40 = L.buf + 0x40;
loop:
    if (ClipCollisionDirect(L.buf, pp50, pv60, gcGlobalVar + 0x238) != 0) {
        *(volatile s128 *)&L.n80 = *GetGeometryPointerSurfacePlane(L.buf);
        *(volatile float *)&L.n80.y = 0.0f;
        vecNormalize(pn80);
        vecScale(pn80, pn80, a);
        vecAdd(po70, pb40, pn80);
        L.o70.w = one;
        setAttainmentPos(work + 0x10, po70);
        *(int *)(work + 0x41D4) = 1;
        return;
    }
    if (retry != 0) {
        *(int *)(work + 0x41D4) = 0;
        return;
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
lqc2 vf6, 0x0(%1)
vsub.xyz vf5, vf5, vf6
sqc2 vf5, 0x0(%2)
"
                         : : "r"(pv60), "r"(pp50), "r"(pn80) : "memory");
    L.n80.y = 0.0f;
    vecNormalize(pn80);
    vecScale(pn80, pn80, b);
    L.v60.y = L.p50.y;
    *(s128 *)&L.p50 = *(s128 *)&L.v60;
    vecAdd(pv60, pv60, pn80);
    L.v60.w = one;
    retry = 1;
    goto loop;
}
#else
void SCRFuncKameSetTemporaryTarget(void *obj, float a, float b);
#endif
