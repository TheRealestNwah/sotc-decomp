typedef float Vec4[4] __attribute__((aligned(16)));
extern char *GetDamageClass(void *);
extern int GetDamagerClassDamageSheetType(char *);
extern char *GetLayoutClass(void *);
extern void GetGeometryPointerPosition(float *, void *);
extern void iosInverseMatrix(float *, float *);
extern float iosGetATan2fExact(float, float);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
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
                         : : "r"(out), "r"(quat));
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(pos) : "memory");
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
extern int isysGetThisSubThread(void);
extern char *GameObject_DORMIN_P;
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void updateUserPathWork(int, void *);
extern void updateHumanCtrlWork(int, void *, void *);
extern void *GetCharacterClass(int);
extern void updateGazeIKWork(void *, int);
extern int D_0017ABBC;
extern int D_0017ABC0;
extern void *memset(void *, int, unsigned int);
extern void setAttainRangeData(void *, float *, float, float, float, float);
extern void getPointPosFromEvent(void *, int, float *);
extern void setAttainmentPos(void *, float *);
extern void _setExecBaseMoveWork(void *, int);
extern int getWayFinish(void *);
extern char *ScriptCtrlDef_SCRGuardSwordPickup;
extern void scrRunM(int);
extern void createUserPathWork(int, void *, float, float, int);
extern void setCreateTempAttain(void *, int);
extern char *GetScriptClass(int);
extern void createHumanCtrlWork(int, void *, int, void *);
extern void setAttainModePathWork(void *, int);
extern void setDashHumanCtrlWork(void *, int);
extern void setUserPathMode(void *, int);
extern void setExecGazeIKWork(void *, int);
extern void setGoingAngleGazeIKWork(void *, float);
extern void SetScriptObjDeleteCallBackFunc(int, void (*)(void), void *);
extern char *GameObject_END_SWORD;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void deleteUserPathWork(char *);
extern char rootPtn[];
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern int ScriptCtrlDef_SCRGuardCDamageFront;
extern int ScriptCtrlDef_SCRGuardCDamageBack;
extern int ScriptCtrlDef_SCRGuardEDamageFront;
extern int ScriptCtrlDef_SCRGuardEDamageBack;

static void func_00055900(void *obj);

void guardDamageMain(void *obj, int *front, int *back)
{
    char *damage = GetDamageClass(obj);
    char *layout;
    Vec4 pos;
    Vec4 dir;
    Vec4 m[4];
    float angle;

    if (*(int *)damage != 1)
        return;
    if (GetDamagerClassDamageSheetType(damage) != 9)
        return;
    layout = GetLayoutClass(obj);
    GetGeometryPointerPosition(pos, damage + 0x10);
    quatPosToMatrix(m[0], *(float **)(layout + 0x13C), *(float **)(layout + 0x134));
    iosInverseMatrix(m[0], m[0]);
    matApply(pos, m[0], pos);
    vecNormalize(dir, pos);
    dir[1] = 0;
    vecNormalize(dir, dir);
    angle = iosGetATan2fExact(dir[0], dir[2]);
    if (-3.1415926f <= angle && angle <= 3.1415926f)
        CharaCtrlSetScriptCtrlStatus(obj, front[1]);
    else
        CharaCtrlSetScriptCtrlStatus(obj, back[1]);
}

static void func_00055580(char *w)
{
    char *p = w + 0x10;
    char *h = w + 0x3C70;
    int th = isysGetThisSubThread();
    float a[4];
    float b[4];

    for (;;) {
        int t = isysGetThisSubThread();
        int obj = *(int *)(GameObject_DORMIN_P + 8);
        void *cc;

        CharaCtrlResetAllScriptCtrlStatus(t);
        updateUserPathWork(t, w + 0x10);
        updateHumanCtrlWork(t, h, w + 0x10);
        cc = GetCharacterClass(t);
        updateGazeIKWork(cc, *(int *)(GetLayoutClass(obj) + 0x134));
        guardDamageMain(th, *(int *)(w + 0x3CB0), *(int *)(w + 0x3CB4));
        if (D_0017ABBC == 0) {
                if (D_0017ABC0 == 0) {
                if (getWayFinish(p) != 0 && *(int *)(w + 0x3CB8) == 0) {
                    CharaCtrlSetScriptCtrlStatus(th, *(int *)(ScriptCtrlDef_SCRGuardSwordPickup + 4));
                    *(int *)(w + 0x3CB8) = 1;
                    D_0017ABC0 = 1;
                }
            } else if (*(int *)(w + 0x3CB8) != 0) {
                _setExecBaseMoveWork(h, 0);
            } else {
                memset(a, 0, 0x10);
                a[3] = 1.0f;
                setAttainRangeData(p, a, 0.0f, 2.0f, 3.1415926f, 10.0f);
            }
        } else {
            memset(b, 0, 0x10);
            b[3] = 1.0f;
            setAttainRangeData(p, b, 0.0f, 1.0f, 3.1415926f, 10.0f);
            getPointPosFromEvent(p, 0, a);
            setAttainmentPos(p, a);
            _setExecBaseMoveWork(h, 1);
        }
        isysGetThisSubThread();
        scrRunM(1);
    }
}

static void func_00055780(char *w)
{
    char *p = w + 0x10;
    int th = isysGetThisSubThread();
    char *h = w + 0x3C70;
    float r[4];

    createUserPathWork(th, p, 5.0f, 10.0f, 0);

    memset(r, 0, 0x10);
    r[3] = 1.0f;
    setAttainRangeData(p, r, 0.0f, 1.0f, 3.1415926f, 10.0f);
    setCreateTempAttain(p, 0);
    setAttainmentPos(p, *(int *)(GetLayoutClass(*(int *)(GameObject_END_SWORD + 8)) + 0x134));
    createHumanCtrlWork(th, h, *(int *)(GetScriptClass(th) + 0x44), p);
    setAttainModePathWork(p, 0);
    _setExecBaseMoveWork(h, 1);
    setDashHumanCtrlWork(h, 1);
    setUserPathMode(p, 0);
    setExecGazeIKWork(GetCharacterClass(th), 1);
    setGoingAngleGazeIKWork(GetCharacterClass(th), 80.0f);
    SetScriptObjDeleteCallBackFunc(th, func_00055900, 0);
    D_0017ABBC = 0;
    D_0017ABC0 = 0;
    *(int *)(w + 0x3CB8) = 0;
}

static void func_00055900(void *obj)
{
    deleteUserPathWork(GetSCRCharaAIWorkPtr(obj) + 0x10);
}

void nico_guardCStart(void)
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
    func_00055780(w);
    *(int *)(w + 0x3CB0) = ScriptCtrlDef_SCRGuardCDamageFront;
    *(int *)(w + 0x3CB4) = ScriptCtrlDef_SCRGuardCDamageBack;
    isysJumpSubThread(func_00055580, w);
}

void nico_guardEStart(void)
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
    func_00055780(w);
    *(int *)(w + 0x3CB0) = ScriptCtrlDef_SCRGuardEDamageFront;
    *(int *)(w + 0x3CB4) = ScriptCtrlDef_SCRGuardEDamageBack;
    isysJumpSubThread(func_00055580, w);
}
