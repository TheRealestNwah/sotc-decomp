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
extern void setRealColJudgeFunc(void *, void (*)(void));
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
extern int *DldSysUndefSymbol;
extern char *GetCharacterClass(void *);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern char *GameObject_CANOSSA_ENV;
extern char *ScriptCtrlDef_SCRCanossaWallBreak;
extern char *SkelFocusDef_MINO_B_Opt_HandR_Front;
extern char *SkelFocusDef_MINO_B_Opt_HandR_Back;
extern char *SkelFocusDef_MINO_B_Opt_HandR_Right;
extern char *SkelFocusDef_MINO_B_Opt_HandL_Front;
extern char *SkelFocusDef_MINO_B_Opt_HandL_Back;
extern char *SkelFocusDef_MINO_B_Opt_HandL_Left;
extern char *SkelFocusDef_MINO_B_Opt_FootR_Front;
extern char *SkelFocusDef_MINO_B_Opt_FootR_Back;
extern char *SkelFocusDef_MINO_B_Opt_FootR_Right;
extern char *SkelFocusDef_MINO_B_Opt_FootL_Front;
extern char *SkelFocusDef_MINO_B_Opt_FootL_Back;
extern char *SkelFocusDef_MINO_B_Opt_FootL_Left;
static inline char *dldData(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
}
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}
static inline float distXZ(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}
extern unsigned long *GetCollisionDBAttributeAdr(void *surface);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void updateScriptDataSystem(void *);
extern void scrRunM(int);

static int func_0006A930(void *surface);
static void func_0006A960(int *boss);
static int T_0006A9C0(void *p, unsigned long *m);

void nico_BossMinotaurStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x4223);
    char *c;
    int *w;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = (int *)_SCRMallocAlign(part, 0x41F0, 0x10);
    *(int **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    setRealColJudgeFunc(w + 4, func_0006A930);
    w[0x41E0 / 4] = 0;
    isysJumpSubThread(func_0006A960, w);
}

void SCRFuncMinoBSetTemporaryTarget(void *obj, int u1, int u2, long long ex, long long ey, float a, float b)
{
    char buf[0x50];
    Pair held;
    char pt[0x10] __attribute__((aligned(16)));
    Vec4 v70;
    Vec4 v80;
    Vec4 v90;
    Vec4 nrm;
    int hit = 0;
    char *work;
    char *attain;
    char *ctrl;

    work = GetSCRCharaAIWorkPtr(obj);
    ctrl = getSCRDataCtrlWork(obj);
    attain = work + 0x10;
    *(s128 *)&v70 = **(s128 **)(*(char **)(ctrl + 0x407C) + 0x134);
    held.x = ex;
    held.y = ey;
    if (getNearPointPosUserPathWork(attain, pt, &v70, 1, -1) != 0) {
        char *grp = gcGlobalVar + 0x238;
        if (ClipCollisionDirectCallBack(buf, pt, &v70, grp, 0, 0, 0, T_0006A9C0, &held) != 0) {
            *(volatile s128 *)&nrm = *GetGeometryPointerSurfacePlane(buf);
            *(volatile float *)&nrm.y = 0.0f;
            vecNormalize(&nrm);
            vecScale(&v80, &nrm, 30.0f);
            vecAdd(&v80, &v70, &v80);
            v80.w = 1.0f;
            if (ClipCollisionDirectCallBack(buf, &v80, &v70, grp, 0, 0, 0, T_0006A9C0, &held) != 0)
                hit = 1;
        }
    } else {
        hit = ClipCollisionDirectCallBack(buf, *(void **)(GetLayoutClass(obj) + 0x134), &v70, gcGlobalVar + 0x238, 0, 0, 0, T_0006A9C0, &held) != 0;
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

void SCRFuncMinoBCanossaWallBreak(void *self, int a1, int a2, int a3, int a4, unsigned int *h, void *vh,
                                  unsigned int *bone, float dist)
{
    char buf[0x60];
    float q[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    char *work = GetSCRCharaAIWorkPtr(self);
    char *obj = dldData(h);
    char *lay;
    int i;

    if (*(int *)(work + 0x41E0) < 4 && obj != 0 && *(void **)(obj + 8) != 0 && GetCharacterClass(*(void **)(obj + 8)) != 0) {
        char **slot = (char **)(GetCharacterClass(*(void **)(obj + 8)) + 0x1C0);

        if (dldResolve(bone) == *slot) {
            bone = 0;
            lay = GetLayoutClass(*(void **)(obj + 8));
            if (__builtin_fabsf(distXZ(*(float **)(lay + 0x134), *(float **)(GetLayoutClass(self) + 0x134))) < dist) {
                for (i = 0; i < 12; i++) {
                    switch (i) {
                    case 0:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandR_Front + 8), 1);
                        break;
                    case 1:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandR_Back + 8), 1);
                        break;
                    case 2:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandR_Right + 8), 1);
                        break;
                    case 3:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandL_Front + 8), 1);
                        break;
                    case 4:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandL_Back + 8), 1);
                        break;
                    case 5:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_HandL_Left + 8), 1);
                        break;
                    case 6:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootR_Front + 8), 1);
                        break;
                    case 7:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootR_Back + 8), 1);
                        break;
                    case 8:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootR_Right + 8), 1);
                        break;
                    case 9:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootL_Front + 8), 1);
                        break;
                    case 10:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootL_Back + 8), 1);
                        break;
                    case 11:
                        GetMotionNodeQuaternionPos(q, pos, self, *(int *)(SkelFocusDef_MINO_B_Opt_FootL_Left + 8), 1);
                        break;
                    }
                    if (*(void **)(GameObject_CANOSSA_ENV + 8) != 0)
                        bone = (unsigned int *)CheckPositionInsideOfJudgeVolumeObject(buf, *(void **)(GameObject_CANOSSA_ENV + 8), vh, pos);
                    if (bone) {
                        CharaCtrlSetScriptCtrlStatus(*(void **)(obj + 8), *(int *)(ScriptCtrlDef_SCRCanossaWallBreak + 4));
                        (*(int *)(work + 0x41E0))++;
                        break;
                    }
                }
            }
        }
    }
}

static int func_0006A930(void *surface)
{
    if (*GetCollisionDBAttributeAdr(surface) & 0x2000000000000000) {
        return 0;
    }
    return 1;
}

static void func_0006A960(int *boss)
{
    void *th;

    isysGetThisSubThread();
    for (;;) {
        th = isysGetThisSubThread();
        SCRExecBossPreProcess(*boss);
        CharaCtrlResetAllScriptCtrlStatus(th);
        updateScriptDataSystem(th);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*boss);
        scrRunM(1);
    }
}

static int T_0006A9C0(void *p, unsigned long *m)
{
    return m[1] == (*GetCollisionDBAttributeAdr(p) & m[0]);
}
