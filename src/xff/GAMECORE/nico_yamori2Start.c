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
extern const float RO_00180D94;
extern void T_000D1388(void);

void nico_yamori2Start(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x4233);
    char *c;
    char *w;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x4200, 0x10);
    *(char **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *(int *)w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    CharaCtrlResetCtrlStatus(th);
    *(int *)(w + 0x41CC) = 0;
    *(int *)(w + 0x41C4) = 0;
    *(int *)(w + 0x41D8) = 0;
    *(float *)(w + 0x41E4) = RO_00180D94;
    *(int *)(w + 0x41DC) = 0;
    *(int *)(w + 0x41D0) = 0;
    *(int *)(w + 0x41D4) = 0;
    *(int *)(w + 0x41E0) = 0;
    *(int *)(w + 0x41E8) = 0;
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    isysJumpSubThread(T_000D1388, w);
}
