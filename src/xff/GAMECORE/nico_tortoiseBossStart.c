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
extern void SetScriptObjDeleteCallBackFunc(void *, void (*)(void), int);
extern void D_000CAA50(void);
extern void func_000CA9F0(void);

void nico_tortoiseBossStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, SCRGetSizeOfBossWork(th) + 0x4223);
    char *c;
    char *w;
    int r;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x41F0, 0x10);
    *(char **)(c + 0x1200) = w;
    r = SCRCharaInitBossWork(part, th);
    *(int *)w = r;
    SetScriptCharacterObjReleaseCallBackFunc(th, SCRReleaseBossWork, r);
    CharaCtrlResetCtrlStatus(th);
    initScriptDataSystem(th, *(int *)(GetScriptClass(th) + 0x48));
    *(int *)(w + 0x41C0) = 0;
    *(int *)(w + 0x41C4) = 0;
    *(int *)(w + 0x41C8) = 0;
    *(int *)(w + 0x41CC) = 0;
    *(int *)(w + 0x41D0) = 0;
    *(int *)(w + 0x41D4) = 0;
    *(int *)(w + 0x41D8) = 0;
    *(int *)(w + 0x41DC) = 0;
    *(int *)(w + 0x41E0) = 0;
    SetScriptObjDeleteCallBackFunc(th, D_000CAA50, 0);
    isysJumpSubThread(func_000CA9F0, w);
}
