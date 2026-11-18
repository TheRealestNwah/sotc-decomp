typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { u_long128 q; Vec4 f; } VecQ;

extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern float *getGoalPointDataByAreaIdx(char *, int, int);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirect(void *, void *, void *, void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern u_long128 *GetGeometryPointerSurfacePlane(void *);
extern float iosGetATan2fExact(float, float);
extern float adjustAnglePI(float);
extern void iosRotMatrixY(float *, float);
extern void setAttainmentPosAndDirPos(char *, void *, void *);
extern char gcGlobalVar[];
extern int func_000946A8();

static inline void vecSub4(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(void *dst, void *src)
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

static inline void matApply(void *d, void *m, void *v)
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
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

static inline void vecScale(void *d, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

static inline void vecAdd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecSub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

void SCRFuncPoseidonParallelTrans(void *chara, int high, int low, float deg, float radius, float step)
{
    char col[0x50];
    VecQ from;
    VecQ to;
    VecQ v80;
    VecQ v90;
    Vec4 mat[4];
    VecQ pos;
    VecQ dir;
    VecQ tgt;
    VecQ nrm;
    VecQ tmp;
    char *ai;
    char *scr;
    float *goal;
    float base;
    float ang;
    int st;

    ai = GetSCRCharaAIWorkPtr(chara);
    scr = getSCRDataCtrlWork(chara);
    goal = getGoalPointDataByAreaIdx(scr, *(int *)(scr + 0x3C90), *(int *)(scr + 0x3C8C));
    from.q = **(u_long128 **)(GetLayoutClass(chara) + 0x134);
    if (high) {
        to.q = **(u_long128 **)(*(char **)(scr + 0x407C) + 0x134);
        from.f[1] = 19.0f;
        to.f[1] = 19.0f;
        if (low) {
            from.f[1] = 11.0f;
            to.f[1] = 11.0f;
        }
        if (ClipCollisionDirect(col, &from, &to, gcGlobalVar + 0x244) == 0) {
            *(int *)(ai + 0x41B0) = 1;
            return;
        }
        *(int *)(ai + 0x41B0) = 0;
    }
    if (goal == 0) {
        return;
    }
    vecSub4(&v80, *(void **)(GetLayoutClass(chara) + 0x134), goal);
    vecSub4(&v90, *(void **)(*(char **)(scr + 0x407C) + 0x134), goal);
    v80.f[1] = 0.0f;
    v90.f[1] = 0.0f;
    vecNormalize(&v80, &v80);
    vecNormalize(&v90, &v90);
    base = iosGetATan2fExact(v80.f[0], v80.f[2]);
    ang = adjustAnglePI(iosGetATan2fExact(v90.f[0], v90.f[2]) - base);
    st = *(int *)(ai + 0x41C8);
    if (st == 0) {
        *(int *)(ai + 0x41C8) = 1;
        if (0.0f <= ang) {
            *(int *)(ai + 0x41C8) = 2;
            st = 2;
        } else {
            st = 1;
        }
    }
    if (st == 2) {
        iosRotMatrixY(mat[0], deg * 0.017453293f);
    } else if (st == 1) {
        iosRotMatrixY(mat[0], -(deg * 0.017453293f));
    } else {
        return;
    }
    v80.f[3] = 0.0f;
    matApply(&pos, mat, &v80);
    vecScale(&pos, &pos, radius);
    vecAdd(&pos, &pos, goal);
    pos.f[3] = 1.0f;
    vecSub(&dir, &pos, &from);
    dir.f[1] = 0.0f;
    vecNormalize(&dir, &dir);
    vecScale(&dir, &dir, step);
    vecAdd(&tgt, &pos, &dir);
    tgt.f[3] = 1.0f;
    if (ClipCollisionDirectCallBack(col, &from, &tgt, gcGlobalVar + 0x238, 0, 0, 0, func_000946A8, 0) != 0) {
        nrm.q = *GetGeometryPointerSurfacePlane(col);
        nrm.f[1] = 0.0f;
        vecNormalize(&nrm, &nrm);
        vecScale(&nrm, &nrm, step);
        vecAdd(&tmp, col + 0x40, &nrm);
        tmp.f[3] = 1.0f;
        vecSub(&nrm, &tmp, goal);
        nrm.f[1] = 0.0f;
        vecNormalize(&nrm, &nrm);
        vecScale(&nrm, &nrm, radius);
        vecAdd(&pos, goal, &nrm);
        st = *(int *)(ai + 0x41C8);
        if (st == 1) {
            *(int *)(ai + 0x41C8) = 2;
        } else if (st == 2) {
            *(int *)(ai + 0x41C8) = 1;
        }
    }
    setAttainmentPosAndDirPos(scr, &pos, goal);
}
