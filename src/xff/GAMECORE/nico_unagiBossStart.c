extern char rootPtn[], gcGlobalVar[], ZeroPoint[], IdentityQuaternion[];
extern int GameObject_EEL_DISCHARGE;
extern int ScriptAnimationObjDef_EEL_THUNDER_A, ScriptAnimationObjDef_EEL_THUNDER_B, ScriptAnimationObjDef_EEL_THUNDER_C;
extern int SkelFocusDef_WORM_HEAD2, SkelFocusDef_WORM_KUBI4, SkelFocusDef_WORM_MUNE4;
extern char D_0017B288[], D_0017B2A0[], D_0017B2B8[], D_0017B2D0[], D_0017B2E8[], D_0017B300[];
extern int isysGetThisSubThread(void);
extern int SCRGetSizeOfBossWork(int);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(int);
extern char *GetLayoutClass(int);
extern char *GetScriptClass(int);
extern void CharaCtrlResetCtrlStatus(int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern char *_SCRMallocAlign(char *, int, int);
extern int SCRCharaInitBossWork(char *, int);
extern void SCRReleaseBossWork(void);
extern void SetScriptCharacterObjReleaseCallBackFunc(int, void *, int);
extern void initScriptDataSystem(int, int);
extern void setRotColCheckWormCtrlWork(char *, int);
extern void setObstacleWormCtrlWork(char *, int);
extern void setTypeWormCtrlWork(char *, int);
extern void setRealColJudgeFunc(char *, void *);
extern void getWormIKWork(int);
extern float getBossPartsLifeRatio(int, int);
extern int _SCRSetupLWSWithTargetNodeParent(int, int, int);
extern void _SCRStartLWS(int, int, int, int);
extern void bootTexAlphaAnim(int, void *, float, float);
extern void scrRun(void);
extern int loadObj(int, void *, void *, void *, int, int);
extern void setDischargeParam(int, void *, float, float);
extern void SetScriptObjDeleteCallBackFunc(int, void *, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern void func_000CC7C0(void);
extern void func_000CC7F8(void);
extern void func_000CC4C0(int);
extern void func_000CB658(void);

#ifdef NONMATCHING /* 244 diffs, 256 vs 272 words: store order of the loadObj request and boss-part flag branches differ */
void nico_unagiBossStart(void)
{
    int req[16] __attribute__((aligned(16)));
    int thr = isysGetThisSubThread();
    char *s0, *s3, *w;
    int s2, i, l, a;
    float zero = 0.0f;
    int *objs;

    s2 = thr;
    iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(s2) + 0x5B73);
    s0 = GetScriptCharacterClass(s2);
    *(char **)(GetScriptCharacterClass(s2) + 0x11FC) = s0;
    CharaCtrlResetCtrlStatus(s2);
    CharaCtrlResetAllScriptCtrlStatus(s2);
    s3 = _SCRMallocAlign(s0, 0x5B40, 0x10);
    *(char **)(GetScriptCharacterClass(s2) + 0x1200) = s3;
    w = s3 + 0x3D20;
    *(int *)s3 = SCRCharaInitBossWork(s0, s2);
    SetScriptCharacterObjReleaseCallBackFunc(s2, (void *)SCRReleaseBossWork, *(int *)s3);
    CharaCtrlResetCtrlStatus(s2);
    initScriptDataSystem(s2, *(int *)(GetScriptClass(s2) + 0x48));
    setRotColCheckWormCtrlWork(w, 1);
    setObstacleWormCtrlWork(w, 1);
    setTypeWormCtrlWork(w, 2);
    setRealColJudgeFunc(s3 + 0x10, (void *)func_000CC7C0);
    getWormIKWork(s2);
    *(int *)(s3 + 0x5ACC) = 0;
    *(int *)(s3 + 0x5A8C) = 0;
    *(int *)(s3 + 0x5A90) = 0;
    *(int *)(s3 + 0x5A94) = 0;
    if (getBossPartsLifeRatio(s2, 0x10) == zero)
        *(int *)(s3 + 0x5A8C) = 1;
    if (getBossPartsLifeRatio(s2, 0x30) == zero)
        *(int *)(s3 + 0x5A90) = 1;
    if (getBossPartsLifeRatio(s2, 0x40) == zero)
        *(int *)(s3 + 0x5A94) = 1;
    a = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_EEL_THUNDER_A, s2, SkelFocusDef_WORM_HEAD2);
    *(int *)(s3 + 0x5A80) = a;
    _SCRStartLWS(a, -1, *(int *)(s3 + 0x5A8C) ? 1 : 5, 0);
    a = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_EEL_THUNDER_B, s2, SkelFocusDef_WORM_KUBI4);
    *(int *)(s3 + 0x5A84) = a;
    _SCRStartLWS(a, -1, *(int *)(s3 + 0x5A90) ? 1 : 5, 0);
    a = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_EEL_THUNDER_C, s2, SkelFocusDef_WORM_MUNE4);
    *(int *)(s3 + 0x5A88) = a;
    _SCRStartLWS(a, -1, *(int *)(s3 + 0x5A94) ? 1 : 5, 0);
    *(int *)(s3 + 0x5A98) = 0;
    *(int *)(s3 + 0x5A9C) = 0;
    *(int *)(s3 + 0x5AA0) = 0;
    bootTexAlphaAnim(s2, D_0017B288, 1.0f, 0.0f);
    bootTexAlphaAnim(s2, D_0017B2A0, 1.0f, 0.0f);
    bootTexAlphaAnim(s2, D_0017B2B8, 1.0f, 0.0f);
    bootTexAlphaAnim(s2, D_0017B2D0, 1.0f, 0.0f);
    bootTexAlphaAnim(s2, D_0017B2E8, 1.0f, 0.0f);
    bootTexAlphaAnim(s2, D_0017B300, 1.0f, 0.0f);
    scrRun();
    func_000CC4C0(s2);
    objs = (int *)(s3 + 0x5AA4);
    for (i = 2; i >= 0; i--) {
        req[0] = (int)ZeroPoint;
        req[1] = (int)ZeroPoint;
        req[2] = (int)IdentityQuaternion;
        req[3] = 0;
        req[4] = 0;
        req[5] = 0;
        req[6] = 0;
        req[7] = 1;
        req[8] = 0;
        req[9] = 0;
        req[10] = 0;
        req[11] = 1;
        req[12] = 0;
        req[13] = 0;
        req[14] = 0;
        *objs = loadObj(GameObject_EEL_DISCHARGE, req, rootPtn, gcGlobalVar + 0x280, 0, 4);
        setDischargeParam(*objs, *(void **)(GetLayoutClass(s2) + 0x134), 0.0f, 0.0f);
        objs++;
    }
    SetScriptObjDeleteCallBackFunc(s2, (void *)func_000CC7F8, 0);
    isysJumpSubThread(func_000CB658, s3);
}
#endif
