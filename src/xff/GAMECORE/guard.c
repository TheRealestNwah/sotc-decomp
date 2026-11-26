/* Shaman's guards: the guard A, B and D scripts, which follow the shaman,
 * face Dormin while he casts, and fire the guard B bowgun. */

typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
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
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(quat), "r"(pos) : "memory");
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

extern char rootPtn[];
extern char *GameObject_SHAMAN_P;
extern char *GameObject_DORMIN_P;
extern int MotionKind_SHAMAN_WALK;
extern int MotionKind_SHAMAN_RUN;
extern int MotionKind_SHAMAN_SPELL_START;
extern int MotionKind_SHAMAN_SPELL_LOOP;
extern int MotionKind_SHAMAN_SPELL_END;
extern char *ScriptCtrlDef_SCRGoR;
extern char *ScriptCtrlDef_SCRGoL;
extern char *ScriptCtrlDef_SCRAccel;
extern int ScriptCtrlDef_SCRGuardADamageFront;
extern int ScriptCtrlDef_SCRGuardADamageBack;
extern int ScriptCtrlDef_SCRGuardAssume;
extern int ScriptCtrlDef_SCRGuardBDamageFront;
extern int ScriptCtrlDef_SCRGuardBDamageBack;
extern int ScriptCtrlDef_SCRGuardDDamageFront;
extern int ScriptCtrlDef_SCRGuardDDamageBack;
extern char gcGlobalVar[];

extern void *isysGetThisSubThread(void);
extern void isysJumpSubThread(void (*)(void), void *);
extern int iosCreatePartition(void *, int);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern int *GetAnimationClass(void *);
extern char *GetScriptClass(void *);
extern char *GetScriptCharacterClass(void *);
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void *memset(void *, int, unsigned int);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void createUserPathWork(void *, void *, int, float, float);
extern void updateUserPathWork(void *, void *);
extern void deleteUserPathWork(char *);
extern void setAttainRangeData(void *, void *, float, float, float, float);
extern void setCreateTempAttain(void *, int);
extern void setAttainModePathWork(void *, int);
extern void setFollowModePathWork(void *, int);
extern void setUserPathMode(void *, int);
extern void setAttainmentPos(void *, float *);
extern int getWayFinish(void *);
extern void createHumanCtrlWork(void *, char *, unsigned int *, void *);
extern void updateHumanCtrlWork(void *, void *, void *);
extern void setDashHumanCtrlWork(void *, int);
extern void _setExecBaseMoveWork(void *, int);
extern void setExecGazeIKWork(void *, int);
extern void setGoingAngleGazeIKWork(void *, float);
extern void updateGazeIKWork(void *, void *);
extern void SetScriptObjDeleteCallBackFunc(void *, void (*)(void), void *);
extern void iosRotMatrixY(float *, float);
extern float iosGetATan2fExact(float, float);
extern float calcProgRotRatio(float, float, float, float, float);
extern void SCRCharaTurnDirectInput(void *, float);
extern void guardDamageMain(void *obj, int front, int back);
extern void scrRunM(int);
extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));

static void func_000562C8(char *w);
static void T_000563E8(void *obj);
static void func_00056408(char *ai);
static void func_00056550(void *obj);
/* In func_00056740.c and T_00056860.c: func_00056740 calls guardMainCommon
 * by name, which a merged file can't reproduce. */
extern void func_00056740(void);
extern void T_00056860(void *character);

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
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

void guardMainCommon(void *obj, int *flag, void *path, void *hc, char *ctrl, float yaw, float scale)
{
    void *sh = *(void **)(GameObject_SHAMAN_P + 8);
    char *ls = GetLayoutClass(sh);
    char *ld = GetLayoutClass(*(void **)(GameObject_DORMIN_P + 8));
    char *lo = GetLayoutClass(obj);
    VecQ d;
    Vec4 rm[4];
    Vec4 m[4];
    VecQ r;
    float a;
    float t;
    char *an;

    *(float *)(GetCharacterClass(obj) + 0x524) = 1.0f;
    if (MotionKind_SHAMAN_WALK == *GetAnimationClass(sh) || MotionKind_SHAMAN_RUN == *GetAnimationClass(sh)) {
        if (distXZ(*(float **)(ls + 0x134), *(float **)(lo + 0x134)) < 3.0f)
            *(float *)(GetCharacterClass(obj) + 0x524) = 0.7f;
        setAttainModePathWork(path, 1);
    } else {
        setAttainModePathWork(path, 0);
    }
    if (distXZ(*(float **)(lo + 0x134), *(float **)(ls + 0x134)) > 5.0f)
        setDashHumanCtrlWork(hc, 1);
    else
        setDashHumanCtrlWork(hc, 0);
    vecSub(d.f, *(float **)(ld + 0x134), *(float **)(ls + 0x134));
    d.f[1] = 0;
    vecNormalize(d.f, d.f);
    d.f[3] = 1.0f;
    iosRotMatrixY(rm[0], yaw);
    matApply(d.f, rm[0], d.f);
    vecScale(d.f, d.f, scale);
    vecAdd(d.f, d.f, *(float **)(ls + 0x134));
    d.f[3] = 1.0f;
    setAttainmentPos(path, d.f);
    if (MotionKind_SHAMAN_SPELL_START == *GetAnimationClass(sh) || MotionKind_SHAMAN_SPELL_LOOP == *GetAnimationClass(sh) ||
        MotionKind_SHAMAN_SPELL_END == *GetAnimationClass(sh)) {
        if (*flag == 0)
            *flag = getWayFinish(path);
        if (*flag != 0) {
        {
            register float *po __asm__("$4") = m[0];
            register float *pq __asm__("$2") = *(float **)(lo + 0x13C);
            register float *pp __asm__("$5") = *(float **)(lo + 0x134);

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
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(po), "r"(pq), "r"(pp));
        }
        {
            register float *pi __asm__("$3") = m[0];

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
                         : : "r"(pi), "r"(pi) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
            matApply(r.f, pi, *(float **)(ld + 0x134));
        }
        r.f[1] = 0;
        vecNormalize(r.f, r.f);
        a = iosGetATan2fExact(r.f[0], r.f[2]);
        if (__builtin_fabsf(a) < 0.087266462f) {
            if (ctrl != 0)
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ctrl + 4));
        } else {
            an = *(char **)GetAnimationClass(obj);
            t = calcProgRotRatio(a, *(int *)(an + 0x74) * 0.017453293f, *(float *)(gcGlobalVar + 0x190),
                                 *(float *)(GetCharacterClass(obj) + 0x72C) * 0.017453293f, *(float *)(an + 0x78));
            if (a > 0.0f) {
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ScriptCtrlDef_SCRGoR + 4));
                SCRCharaTurnDirectInput(obj, t);
            } else if (a < 0.0f) {
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ScriptCtrlDef_SCRGoL + 4));
                SCRCharaTurnDirectInput(obj, -t);
            }
            CharaCtrlSetScriptCtrlStatus(obj, *(int *)(ScriptCtrlDef_SCRAccel + 4));
        }
        _setExecBaseMoveWork(hc, 0);
        } else {
            _setExecBaseMoveWork(hc, 1);
        }
    } else {
        _setExecBaseMoveWork(hc, 1);
        *flag = 0;
    }
}

void nico_guardAStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x3CE3);
    char *c;
    char *w;
    char *pw;
    char *hc;
    float v[4];

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x3CB0, 0x10);
    *(char **)(c + 0x1200) = w;
    hc = w + 0x3C70;
    pw = w + 0x10;
    CharaCtrlResetCtrlStatus(th);
    createUserPathWork(th, pw, 0, 5.0f, 10.0f);
    memset(v, 0, 0x10);
    v[3] = 1.0f;
    setAttainRangeData(pw, v, 0.0f, 0.5f, 3.1415926f, 10.0f);
    setCreateTempAttain(pw, 0);
    createHumanCtrlWork(th, hc, *(unsigned int **)(GetScriptClass(th) + 0x44), pw);
    setAttainModePathWork(pw, 0);
    setFollowModePathWork(pw, 1);
    _setExecBaseMoveWork(hc, 1);
    setUserPathMode(pw, 0);
    setExecGazeIKWork(GetCharacterClass(th), 1);
    setGoingAngleGazeIKWork(GetCharacterClass(th), 80.0f);
    SetScriptObjDeleteCallBackFunc(th, (void (*)(void))T_000563E8, 0);
    isysJumpSubThread((void (*)(void))func_000562C8, w);
}

static void func_000562C8(char *w)
{
    void *th = isysGetThisSubThread();
    char *hc = w + 0x3C70;
    char *pw = w + 0x10;
    int state = 0;

    while (1) {
        void *t = isysGetThisSubThread();
        void *obj = *(void **)(GameObject_DORMIN_P + 8);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateUserPathWork(t, w + 0x10);
        updateHumanCtrlWork(t, hc, w + 0x10);
        updateGazeIKWork(GetCharacterClass(t), *(void **)(GetLayoutClass(obj) + 0x134));
        guardDamageMain(th, ScriptCtrlDef_SCRGuardADamageFront, ScriptCtrlDef_SCRGuardADamageBack);
        if (*(int *)(GameObject_SHAMAN_P + 8) != 0 && *(int *)(GameObject_DORMIN_P + 8) != 0)
            guardMainCommon(th, &state, pw, hc, (char *)ScriptCtrlDef_SCRGuardAssume, 0.0f, 1.5f);
        isysGetThisSubThread();
        scrRunM(1);
    }
}

static void T_000563E8(void *obj)
{
    deleteUserPathWork(GetSCRCharaAIWorkPtr(obj) + 0x10);
}

static void func_00056408(char *ai)
{
    float range[4];
    void *thread;
    char *human = ai + 0x3C70;
    char *path = ai + 0x10;

    thread = isysGetThisSubThread();

    createUserPathWork(thread, path, 0, 5.0f, 10.0f);
    memset(range, 0, sizeof(range));
    range[3] = 1.0f;
    setAttainRangeData(path, range, 0.0f, 1.0f, 3.1415926f, 10.0f);
    setCreateTempAttain(path, 0);
    createHumanCtrlWork(thread, human, *(unsigned int **)(GetScriptClass(thread) + 0x44), path);
    setAttainModePathWork(path, 0);
    setFollowModePathWork(path, 1);
    _setExecBaseMoveWork(human, 1);
    setUserPathMode(path, 0);
    setExecGazeIKWork(GetCharacterClass(thread), 1);
    setGoingAngleGazeIKWork(GetCharacterClass(thread), 80.0f);
    SetScriptObjDeleteCallBackFunc(thread, (void (*)(void))func_00056550, 0);
}

static void func_00056550(void *obj)
{
    deleteUserPathWork(GetSCRCharaAIWorkPtr(obj) + 0x10);
}

void nico_guardBStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x3CF3);
    char *c;
    char *w;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x3CC0, 0x10);
    *(char **)(c + 0x1200) = w;
    CharaCtrlResetCtrlStatus(th);
    func_00056408(w);
    *(float *)(w + 0x3CB0) = 1.0471975803375244f;
    *(int *)(w + 0x3CB4) = ScriptCtrlDef_SCRGuardBDamageFront;
    *(int *)(w + 0x3CB8) = ScriptCtrlDef_SCRGuardBDamageBack;
    scrRunM(1);
    isysJumpSubThread(func_00056740, w);
}

void nico_guardDStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x3CF3);
    char *c;
    char *w;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x3CC0, 0x10);
    *(char **)(c + 0x1200) = w;
    CharaCtrlResetCtrlStatus(th);
    func_00056408(w);
    *(float *)(w + 0x3CB0) = -1.0471975803375244f;
    *(int *)(w + 0x3CB4) = ScriptCtrlDef_SCRGuardDDamageFront;
    *(int *)(w + 0x3CB8) = ScriptCtrlDef_SCRGuardDDamageBack;
    scrRunM(1);
    isysJumpSubThread(func_00056740, w);
}

void SCRGuardArrowShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, T_00056860);
}
