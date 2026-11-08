typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern int getNearPointPosUserPathWork(void *, void *, void *, int, int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern s128 *GetGeometryPointerSurfacePlane(void *);
extern void setAttainmentPosAndDir(void *, void *, void *);
extern int T_0006B070(void *);

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

void SCRFuncMinoASetTemporaryTarget(void *obj, float a, float b)
{
    char buf[0x50];
    char pt[0x10] __attribute__((aligned(16)));
    Vec4 v70;
    Vec4 v80;
    Vec4 v90;
    Vec4 nrm;
    int hit = 0;
    char *work = GetSCRCharaAIWorkPtr(obj);
    char *attain;
    char *ctrl;

    ctrl = getSCRDataCtrlWork(obj);
    attain = work + 0x10;
    *(s128 *)&v70 = **(s128 **)(*(char **)(ctrl + 0x407C) + 0x134);
    if (getNearPointPosUserPathWork(attain, pt, &v70, 1, -1) != 0) {
        char *grp = gcGlobalVar + 0x238;
        if (ClipCollisionDirectCallBack(buf, pt, &v70, grp, 0, 0, 0, T_0006B070, 0) != 0) {
            *(volatile s128 *)&nrm = *GetGeometryPointerSurfacePlane(buf);
            *(volatile float *)&nrm.y = 0.0f;
            vecNormalize(&nrm);
            vecScale(&v80, &nrm, 30.0f);
            vecAdd(&v80, &v70, &v80);
            v80.w = 1.0f;
            if (ClipCollisionDirectCallBack(buf, &v80, &v70, grp, 0, 0, 0, T_0006B070, 0) != 0)
                hit = 1;
        }
    } else {
        hit = ClipCollisionDirectCallBack(buf, *(void **)(GetLayoutClass(obj) + 0x134), &v70, gcGlobalVar + 0x238, 0, 0, 0, T_0006B070, 0) != 0;
    }
    if (hit != 0) {
        *(volatile s128 *)&nrm = *GetGeometryPointerSurfacePlane(buf);
        *(volatile float *)&nrm.y = 0.0f;
        vecNormalize(&nrm);
        vecScale(&v80, &nrm, a);
        vecAdd(&v80, buf + 0x40, &v80);
        v80.y += b;
        v80.w = 1.0f;
        vecScale(&v90, &nrm, -1.0f);
        v90.w = 1.0f;
        setAttainmentPosAndDir(attain, &v80, &v90);
    }
}
