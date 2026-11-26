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
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void updateScriptDataSystem(void *);
extern void scrRunM(int);
extern unsigned long *GetCollisionDBAttributeAdr(void *);
extern void isysRequestDeleteObj(int);
extern void GetMotionNodeQuaternionPos(Vec4 *, Vec4 *, void *, int, int);
extern void StabilizeToYRotQuaternion(Vec4 *);
extern void ForceUnparentLayoutObj(int);
extern void SCRSetLWSGeometryWithZY(int, int, Vec4 *, Vec4 *, Vec4 *);
extern void _SCRStartLWS(int, int, int, int);
extern char *SkelFocusDef_MINOTAUR_SWORD;
extern Vec4 YUnitVector;
extern int ScriptAnimationObjDef_MINO_C_WEAPON_DEFAULT;
extern int ScriptAnimationObjDef_MINO_C_WEAPON_FALL;
extern int _gameFlagChk(int);
extern int _SCRSetupLWSWithTargetNodeParent(int, void *, int *);

static void func_0006B010(int *boss);
static int T_0006B070(void *p);

void nico_BossMinotaurAStart(void)
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
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    isysJumpSubThread(func_0006B010, w);
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

static void func_0006B010(int *boss)
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

static int T_0006B070(void *p)
{
    return (*GetCollisionDBAttributeAdr(p) & 0x7C000000) == 0x64000000;
}

static void func_0006B0A8(char *w)
{
    void *th = isysGetThisSubThread();
    Vec4 pos;
    Vec4 dir;
    Vec4 q;

    while (1) {
        void *t = isysGetThisSubThread();
        SCRExecBossPreProcess(*(int *)w);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateScriptDataSystem(t);
        if (*(int *)(w + 0x4200) != 0) {
            isysRequestDeleteObj(*(int *)(w + 0x41E0));
            GetMotionNodeQuaternionPos(&q, &pos, th, *(int *)(SkelFocusDef_MINOTAUR_SWORD + 8), 1);
            StabilizeToYRotQuaternion(&q);
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
                                 : : "r"(&dir), "r"(&q) : "memory");
            ForceUnparentLayoutObj(*(int *)(w + 0x41E4));
            SCRSetLWSGeometryWithZY(*(int *)(w + 0x41E4), 0, &pos, &dir, &YUnitVector);
            _SCRStartLWS(*(int *)(w + 0x41E4), -1, 4, 0);
            *(int *)(w + 0x4200) = 0;
        }
        isysGetThisSubThread();
        SCRExecBossPostProcess(*(int *)w);
        scrRunM(1);
    }
}

void nico_BossMinotaurCStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x4243);
    char *c;
    int *w;
    int r;
    int lws;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = (int *)_SCRMallocAlign(part, 0x4210, 0x10);
    *(int **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    w[0x41E8 / 4] = 0;
    w[0x41EC / 4] = 0;
    w[0x41F0 / 4] = 0;
    w[0x41F4 / 4] = 0;
    w[0x41F8 / 4] = 1;
    w[0x41FC / 4] = 0;
    w[0x4200 / 4] = 0;
    if (!_gameFlagChk(0x13F)) {
        lws = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_MINO_C_WEAPON_DEFAULT, th, (*(int * *)&SkelFocusDef_MINOTAUR_SWORD));
        w[0x41E0 / 4] = lws;
        _SCRStartLWS(lws, -1, 2, 0);
        lws = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_MINO_C_WEAPON_FALL, th, (*(int * *)&SkelFocusDef_MINOTAUR_SWORD));
        w[0x41E4 / 4] = lws;
        _SCRStartLWS(lws, -1, 1, 0);
    } else {
        w[0x41E4 / 4] = 0;
        w[0x41E0 / 4] = 0;
    }
    isysJumpSubThread(func_0006B0A8, w);
}
