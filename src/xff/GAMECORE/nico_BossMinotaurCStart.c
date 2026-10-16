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
extern int *SkelFocusDef_MINOTAUR_SWORD;
extern int ScriptAnimationObjDef_MINO_C_WEAPON_DEFAULT;
extern int ScriptAnimationObjDef_MINO_C_WEAPON_FALL;
extern int _gameFlagChk(int);
extern int _SCRSetupLWSWithTargetNodeParent(int, void *, int *);
extern void _SCRStartLWS(int, int, int, int *);
extern void func_0006B0A8(void);

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
        lws = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_MINO_C_WEAPON_DEFAULT, th, SkelFocusDef_MINOTAUR_SWORD);
        w[0x41E0 / 4] = lws;
        _SCRStartLWS(lws, -1, 2, 0);
        lws = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_MINO_C_WEAPON_FALL, th, SkelFocusDef_MINOTAUR_SWORD);
        w[0x41E4 / 4] = lws;
        _SCRStartLWS(lws, -1, 1, 0);
    } else {
        w[0x41E4 / 4] = 0;
        w[0x41E0 / 4] = 0;
    }
    isysJumpSubThread(func_0006B0A8, w);
}
