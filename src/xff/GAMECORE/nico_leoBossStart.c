/* The torch access-switch call is declared volatile (permuter find) to get the Original register choice for the torch loads. */
extern char rootPtn[];
extern int SkelFocusDef_LEO_NECK_A;
extern int SkelFocusDef_LEO_CHEST;
extern int SkelFocusDef_LEO_WAIST;
extern int SkelFocusDef_LEO_TAIL_A;
extern int ScriptAnimationObjDef_LEO_ARMER0;
extern int ScriptAnimationObjDef_LEO_ARMER1;
extern int ScriptAnimationObjDef_LEO_ARMER2;
extern int ScriptAnimationObjDef_LEO_ARMER3;
extern char *StageLayout_LEO_TORCH0;
extern char *StageLayout_LEO_TORCH1;
extern char *StageLayout_LEO_TORCH2;
extern char *StageLayout_LEO_TORCH3;
extern int B_0018AF80;
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
extern void scrRunM(int);
extern int _gameFlagChk(int);
extern int _SCRSetupLWSWithTargetNodeParent(int, void *, int);
extern void _SCRStartLWS(int, int, int, int);
extern volatile int SetLayoutObjAccessSwitch(int, int);
extern void SetScriptObjDeleteCallBackFunc(void *, void (*)(void), int);
extern void func_00064200(void);
extern void func_00063C70(void);

void nico_leoBossStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x4203);
    char *c;
    int *w;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = (int *)_SCRMallocAlign(part, 0x41D0, 0x10);
    *(int **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    scrRunM(1);
    CharaCtrlResetCtrlStatus(th);
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    if (_gameFlagChk(0x125) == 0) {
        w[0x41B0 / 4] = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_LEO_ARMER0, th, SkelFocusDef_LEO_NECK_A);
        _SCRStartLWS(w[0x41B0 / 4], -1, 2, 0);
        w[0x41B4 / 4] = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_LEO_ARMER1, th, SkelFocusDef_LEO_CHEST);
        _SCRStartLWS(w[0x41B4 / 4], -1, 2, 0);
        w[0x41B8 / 4] = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_LEO_ARMER2, th, SkelFocusDef_LEO_WAIST);
        _SCRStartLWS(w[0x41B8 / 4], -1, 2, 0);
        w[0x41BC / 4] = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_LEO_ARMER3, th, SkelFocusDef_LEO_TAIL_A);
        _SCRStartLWS(w[0x41BC / 4], -1, 2, 0);
        w[0x41C0 / 4] = 0;
    } else {
        w[0x41C0 / 4] = 2;
    }
    B_0018AF80 = 0;
    {
        char *t;

        t = StageLayout_LEO_TORCH0;
        SetLayoutObjAccessSwitch(*(int *)(t + 0x48), 0);
        t = StageLayout_LEO_TORCH1;
        SetLayoutObjAccessSwitch(*(int *)(t + 0x48), 0);
        t = StageLayout_LEO_TORCH2;
        SetLayoutObjAccessSwitch(*(int *)(t + 0x48), 0);
        t = StageLayout_LEO_TORCH3;
        SetLayoutObjAccessSwitch(*(int *)(t + 0x48), 0);
    }
    SetScriptObjDeleteCallBackFunc(th, func_00064200, 0);
    isysJumpSubThread(func_00063C70, w);
}
