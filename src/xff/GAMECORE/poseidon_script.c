extern void *GetCharacterClass(void *);
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void *memset(void *, int, unsigned int);
extern char *SkelFocusDef_BOSS_OPT_ATTACK;
extern void GetMotionNodeQuaternionPos(Vec4 *, Vec4 *, void *, int, int);
extern char *GetLayoutClass(void *);
extern float iosGetRandom(void);
extern void iosRotMatrixY(Vec4 *, float);
static inline void vecSub4(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
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
static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}
static inline void vecAdd1(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
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
extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern int SCRGetSizeOfBossWork(void *);
extern int SCRCharaInitBossWork(int, void *);
extern void SCRReleaseBossWork(void);
extern void SetScriptCharacterObjReleaseCallBackFunc(void *, void (*)(void), int);
extern char *GetScriptClass(void *);
extern void initScriptDataSystem(void *, int);
typedef float Vec4_SCRFuncPoseidonParallelTrans[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { u_long128 q; Vec4_SCRFuncPoseidonParallelTrans f; } VecQ;
extern char *getSCRDataCtrlWork(void *);
extern float *getGoalPointDataByAreaIdx(char *, int, int);
extern int ClipCollisionDirect(void *, void *, void *, void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern u_long128 *GetGeometryPointerSurfacePlane(void *);
extern float iosGetATan2fExact(float, float);
extern float adjustAnglePI(float);
extern void setAttainmentPosAndDirPos(char *, void *, void *);
extern char gcGlobalVar[];
static inline void vecSub4_SCRFuncPoseidonParallelTrans(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void vecNormalize_SCRFuncPoseidonParallelTrans(void *dst, void *src)
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
static inline void matApply_SCRFuncPoseidonParallelTrans(void *d, void *m, void *v)
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
static inline void vecScale_SCRFuncPoseidonParallelTrans(void *d, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}
static inline void vecAddV(void *d, void *a, void *b)
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
extern char ZDirVector[];
extern int setAttainmentPosAndDirAndLock(void *, float *, float *);
static const unsigned int RO_NoLimit = 0xFFFFFFFF;
static inline void vecScaleXYZ(float *out, float *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni %2, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}
static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
typedef float Vec4_func_00094340[4] __attribute__((aligned(16)));
typedef union {
    u_long128 q;
    Vec4_func_00094340 f;
} VecQ_func_00094340;
extern void SCRGetCharNodePos(float *, void *, int);
extern void GetQuaternionByAxisDirZY(float *, float *, float *);
extern void SCRSetupMissile1(void *, float *, float *, int);
static inline void vecDirection(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vsub.xyzw vf6, vf4, vf5\n"
                         "vmul.xyz vf5, vf6, vf6\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "vsqrt Q, vf5x\n"
                         "vwaitq\n"
                         "vaddq.x vf5, vf0, Q\n"
                         "vdiv Q, vf0w, vf5x\n"
                         "vsub.xyzw vf7, vf0, vf0\n"
                         "vwaitq\n"
                         "vmulq.xyz vf7, vf6, Q\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b));
}
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void updateScriptDataSystem(void *);
extern void scrRunM(int);
extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern char D_0017AEC8[];
extern void bootTexAlphaAnim(void *, void *, float, float);
extern char D_0017AEE0[];
extern char D_0017AEF8[];
extern long *GetCollisionDBAttributeAdr(void *);
#define NULL ((void *)0)
extern void *getRootPointDataByAreaIdx(void *, int, int);
extern unsigned char RO_0017F688[];

static void func_00094340(void *obj, float *tgt, int node);
static void func_000943E8(int *boss);
static int func_000946A8(void *collision);

float SCRGetPlayerTiredParam(void *actor)
{
  char *character = GetCharacterClass(actor);
  float *velocity;
  if ((!character) || (!(*((int *) (character + 0x124)))))
  {
    return 0.0f;
  }
  velocity = (float *) ((*((char **) (character + 0x19C))) + 0x88);
  {
    float value0 = *velocity;
    if ((value0 < 0.0f) ? (value0 < (-10.0f)) : (value0 > 10.0f))
    {
      return 0.1f;
    }
  }
  {
    float value1 = *((float *) ((*((char **) (character + 0x19C))) + 0x88));
    if ((value1 < 0.0f) ? (value1 < (-3.0f)) : (value1 > 3.0f))
    {
      return 0.03f;
    }
  }
  {
    float value2 = *((float *) ((*((char **) (character + 0x19C))) + 0x88));
    if ((value2 < 0.0f) ? (value2 < (-1.0f)) : (1.0f < value2))
    {
      return 0.01f;
    }
  }
  return 0.0f;
}

static void func_000939A0(void *obj)
{
    char *ai = GetSCRCharaAIWorkPtr(obj);
    Vec4 ofs;
    Vec4 pos;
    Vec4 quat;
    Vec4 rot[4];
    Vec4 npos;
    Vec4 *p;
    char *lay;

    memset(&ofs, 0, 0x10);
    ofs.f[3] = 1.0f;
    GetMotionNodeQuaternionPos(&npos, &quat, obj, *(int *)(SkelFocusDef_BOSS_OPT_ATTACK + 8), 1);
    lay = GetLayoutClass(obj);
    p = &pos;
    vecSub4(p->f, *(float **)(lay + 0x134), *(float **)(*(char **)(ai + 0x408C) + 0x134));
    p->f[1] = 0.0f;
    vecNormalize(p->f);
    vecScale(p->f, p->f, 0.1f);
    vecAdd1(p->f, p->f, *(float **)(*(char **)(ai + 0x408C) + 0x134));
    ofs.f[2] = iosGetRandom() * 0.03f;
    iosRotMatrixY(rot, iosGetRandom() * 3.14159265f * 2.0f);
    matApply(ofs.f, rot[0].f, ofs.f);
    vecAdd1(ofs.f, ofs.f, p->f);
    ((void (*)(void *, Vec4 *, char *))func_00094340)(obj, &ofs, SkelFocusDef_BOSS_OPT_ATTACK);
}

void nico_poseidonStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x4213);
    char *c;
    int *w;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = (int *)_SCRMallocAlign(part, 0x41E0, 0x10);
    *(int **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    CharaCtrlResetCtrlStatus(th);
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    w[0x41C8 / 4] = 0;
    w[0x41B0 / 4] = 0;
    w[0x41CC / 4] = 0;
    w[0x41B4 / 4] = 0;
    w[0x41BC / 4] = 0;
    w[0x41C0 / 4] = 0;
    w[0x41D0 / 4] = 0;
    w[0x41D4 / 4] = 0;
    w[0x41D8 / 4] = 0;
    w[0x41DC / 4] = 0;
    ((char *)GetCharacterClass(th))[0x538] = 1;
    isysJumpSubThread(func_000943E8, w);
}

void SCRFuncPoseidonParallelTrans(void *chara, int high, int low, float deg, float radius, float step)
{
    char col[0x50];
    VecQ from;
    VecQ to;
    VecQ v80;
    VecQ v90;
    Vec4_SCRFuncPoseidonParallelTrans mat[4];
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
    vecSub4_SCRFuncPoseidonParallelTrans(&v80, *(void **)(GetLayoutClass(chara) + 0x134), goal);
    vecSub4_SCRFuncPoseidonParallelTrans(&v90, *(void **)(*(char **)(scr + 0x407C) + 0x134), goal);
    v80.f[1] = 0.0f;
    v90.f[1] = 0.0f;
    vecNormalize_SCRFuncPoseidonParallelTrans(&v80, &v80);
    vecNormalize_SCRFuncPoseidonParallelTrans(&v90, &v90);
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
        ((void (*)(float *, float))iosRotMatrixY)(mat[0], deg * 0.017453293f);
    } else if (st == 1) {
        ((void (*)(float *, float))iosRotMatrixY)(mat[0], -(deg * 0.017453293f));
    } else {
        return;
    }
    v80.f[3] = 0.0f;
    matApply_SCRFuncPoseidonParallelTrans(&pos, mat, &v80);
    vecScale_SCRFuncPoseidonParallelTrans(&pos, &pos, radius);
    vecAddV(&pos, &pos, goal);
    pos.f[3] = 1.0f;
    vecSub(&dir, &pos, &from);
    dir.f[1] = 0.0f;
    vecNormalize_SCRFuncPoseidonParallelTrans(&dir, &dir);
    vecScale_SCRFuncPoseidonParallelTrans(&dir, &dir, step);
    vecAddV(&tgt, &pos, &dir);
    tgt.f[3] = 1.0f;
    if (ClipCollisionDirectCallBack(col, &from, &tgt, gcGlobalVar + 0x238, 0, 0, 0, func_000946A8, 0) != 0) {
        nrm.q = *GetGeometryPointerSurfacePlane(col);
        nrm.f[1] = 0.0f;
        vecNormalize_SCRFuncPoseidonParallelTrans(&nrm, &nrm);
        vecScale_SCRFuncPoseidonParallelTrans(&nrm, &nrm, step);
        vecAddV(&tmp, col + 0x40, &nrm);
        tmp.f[3] = 1.0f;
        vecSub(&nrm, &tmp, goal);
        nrm.f[1] = 0.0f;
        vecNormalize_SCRFuncPoseidonParallelTrans(&nrm, &nrm);
        vecScale_SCRFuncPoseidonParallelTrans(&nrm, &nrm, radius);
        vecAddV(&pos, goal, &nrm);
        st = *(int *)(ai + 0x41C8);
        if (st == 1) {
            *(int *)(ai + 0x41C8) = 2;
        } else if (st == 2) {
            *(int *)(ai + 0x41C8) = 1;
        }
    }
    setAttainmentPosAndDirPos(scr, &pos, goal);
}

static int func_000940A0(void *unused, float *lim)
{
    float v[4] __attribute__((aligned(16)));
    float m[16] __attribute__((aligned(16)));
    float p[4] __attribute__((aligned(16)));
    char *w = getSCRDataCtrlWork(unused);
    float *goal = ((float * (*)(void *, int, int))getGoalPointDataByAreaIdx)(w, *(int *)(w + 0x3C90), *(int *)(w + 0x3C8C));
    float cur, lo, hi, mid, h;
    int i, hit = 0;
    char *e8;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(v), "r"(w + 0x70), "r"(goal) : "memory");
    v[1] = 0.0f;
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
    cur = iosGetATan2fExact(v[0], v[2]);
    e8 = (char *)lim + 8;
    for (i = 0; i < 3; i++) {
        float nl = *(const float *)&RO_NoLimit;
        register int off __asm__("$3") = i * 8;
        float a;
        a = *(float *)(e8 + off);
        __asm__("" : "+r"(off));
        if (a != nl) {
        lo = a * 0.017453293f;
        { register char *hp __asm__("$2") = (char *)lim + off; hi = *(float *)(hp + 0xC) * 0.017453293f; }
        if (lo <= hi) {
            h = (hi - lo) * 0.5f; mid = lo + h;
            if (lo <= cur && cur <= mid) {
                cur = lo;
                hit = 1;
            } else if (mid <= cur && cur <= hi) {
                cur = hi;
                hit = 1;
            }
        } else {
            /* Both branches go through h, so the 2pi-span half lands in $f0 like the (hi - lo) one. */
            h = (6.28318548f - (lo - hi)) * 0.5f; mid = adjustAnglePI(lo + h);
            if (mid >= 0.0f) {
                if (lo <= cur) {
                    if (cur <= mid) cur = lo; else cur = hi;
                    hit = 1;
                } else if (cur <= hi) {
                    cur = hi;
                    hit = 1;
                }
            } else {
                if (lo <= cur) {
                    cur = lo;
                    hit = 1;
                } else if (cur <= hi) {
                    if (cur <= mid) cur = lo; else cur = hi;
                    hit = 1;
                }
            }
        }
        }
        if (hit)
            break;
    }
    ((void (*)(float *, float))iosRotMatrixY)(m, cur);
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf14, 0x0(%2)\n"
                         "lqc2 vf15, 0x10(%2)\n"
                         "lqc2 vf16, 0x20(%2)\n"
                         "lqc2 vf17, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(v), "r"(ZDirVector), "r"(m) : "memory");
    vecScaleXYZ(p, v, *(float *)(w + 0x3C84));
    vecAdd(p, p, goal);
    vecScaleXYZ(v, v, -1.0f);
    return setAttainmentPosAndDirAndLock(w, p, v);
}

static void func_00094340(void *obj, float *tgt, int node)
{
    Vec4_func_00094340 q;
    Vec4_func_00094340 pos;
    Vec4_func_00094340 dir;

    SCRGetCharNodePos(pos, obj, node);
    vecDirection(dir, tgt, pos);
    GetQuaternionByAxisDirZY(q, dir, dir);
    SCRSetupMissile1(obj, pos, q, 1);
}

static void func_000943E8(int *boss)
{
    isysGetThisSubThread();
    for (;;) {
        void *th = isysGetThisSubThread();

        SCRExecBossPreProcess(*boss);
        CharaCtrlResetAllScriptCtrlStatus(th);
        updateScriptDataSystem(th);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*boss);
        scrRunM(1);
    }
}

void SCRPoseidonShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_000939A0);
}

void nico_poseidonToothFTexAnimStrat(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AEC8, 1.0f, 0.05f);
}

void nico_poseidonToothFTexAnimEnd(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AEC8, 0.0f, -0.05f);
}

void nico_poseidonToothRTexAnimStrat(void)
{
    void *t = isysGetThisSubThread();
    ((void (*)(void *, int *, float, float))bootTexAlphaAnim)(t, D_0017AEE0, 1.0f, 0.05f);
    ((void (*)(void *, int *, float, float))bootTexAlphaAnim)(t, D_0017AEC8, 0.0f, -0.05f);
}

void nico_poseidonToothRTexAnimEnd(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AEE0, 0.0f, -0.05f);
}

void nico_poseidonToothLTexAnimStrat(void)
{
    void *t = isysGetThisSubThread();
    ((void (*)(void *, int *, float, float))bootTexAlphaAnim)(t, D_0017AEF8, 1.0f, 0.05f);
    ((void (*)(void *, int *, float, float))bootTexAlphaAnim)(t, D_0017AEC8, 0.0f, -0.05f);
}

void nico_poseidonToothLTexAnimEnd(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AEF8, 0.0f, -0.05f);
}

void nico_poseidonToothTexAnimInit(void)
{
    void *th = isysGetThisSubThread();

    bootTexAlphaAnim(th, D_0017AEE0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AEF8, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AEC8, 0.0f, -0.05f);
}

static int func_000946A8(void *collision)
{
    return (*GetCollisionDBAttributeAdr(collision) & 0xF80000000) == 0x780000000;
}

int SCRConditoinPoseidonPlayerRayChack(void *actor, int interval)
{
    char *work = getSCRDataCtrlWork(actor);
    char hit[0x50];

    if ((int)*(float *)(work + 0x40A4) % interval > 0)
        return 0;
    return ((int (*)(void *, float *, float *, void *))ClipCollisionDirect)(hit, *(float **)(GetLayoutClass(actor) + 0x134),
                               *(float **)(*(char **)(work + 0x407C) + 0x134), gcGlobalVar + 0x244) == 0;
}

void SCRFuncPoseidonModifyGP2AttainPos(void *arg0) {
    void *var_s0;
    int temp_v1;
    int var_s1;
    void *temp_s2;
    void *temp_s4;
    void *temp_v0;

    temp_s4 = GetSCRCharaAIWorkPtr(arg0);
    temp_v0 = getSCRDataCtrlWork(arg0);
    temp_s2 = getRootPointDataByAreaIdx(temp_v0, (*(int *)((char *)(temp_v0) + 0x3C88)), (*(int *)((char *)(temp_v0) + 0x3C8C)));
    if ((*(int *)((char *)(temp_v0) + 0x4094)) != 0) {
        (*(int *)((char *)(temp_s4) + 0x41B4)) = 1;
    } else if (temp_s2 != NULL) {
        if ((*(int *)((char *)(temp_s4) + 0x41B4)) != 0) {
            var_s1 = 4;
            var_s0 = RO_0017F688;
            do {
                temp_v1 = (*(int *)((char *)(temp_s2) + 0x10));
                if (temp_v1 != (*(int *)((char *)(var_s0) + 0))) {
                    if (temp_v1 == (*(int *)((char *)(var_s0) + 4))) {
                        goto block_9;
                    }
                } else {
block_9:
                    ((void (*)(void *, void *))func_000940A0)(arg0, var_s0);
                }
                var_s1 -= 1;
                var_s0 += 0x20;
            } while (var_s1 >= 0);
        }
        (*(int *)((char *)(temp_s4) + 0x41B4)) = 0;
    }
}
