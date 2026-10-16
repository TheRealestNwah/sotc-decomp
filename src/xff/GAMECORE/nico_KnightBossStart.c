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
extern int *GameObject_KNIGHT_ARM_PARTS;
extern int *GameObject_KNIGHT_ARM_BREAK;
extern int *GameObject_KNIGHT_NECK_PARTS;
extern int *GameObject_KNIGHT_NECK_BREAK;
extern int _gameFlagChk(int);
extern void _SCRStartLWS(int, int, int, int *);
extern void func_00063820(void);

void nico_KnightBossStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x41F3);
    char *c;
    int *w;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = (int *)_SCRMallocAlign(part, 0x41C0, 0x10);
    *(int **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    CharaCtrlResetCtrlStatus(th);
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    w[0x41B0 / 4] = 0;
    w[0x41B4 / 4] = 0;
    w[0x41B8 / 4] = 0;
    if (_gameFlagChk(0x10A)) {
        _SCRStartLWS(GameObject_KNIGHT_ARM_PARTS[2], -1, 1, 0);
        _SCRStartLWS(GameObject_KNIGHT_ARM_BREAK[2], -1, 1, 0);
    }
    if (_gameFlagChk(0x10B)) {
        _SCRStartLWS(GameObject_KNIGHT_NECK_PARTS[2], -1, 1, 0);
        _SCRStartLWS(GameObject_KNIGHT_NECK_BREAK[2], -1, 1, 0);
    }
    isysJumpSubThread(func_00063820, w);
}
