extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern char gcGlobalVar[];
extern char *GetScriptClass(void *);
extern int getEditWorkInitData(int);
extern void *SCRGetFirstObj(void *);
extern void scrRun(void);
extern void AI_InitAnimalWork(void *, int);
extern void func_000B2890(void *);
extern void func_000B1D88(void);

void nico_SmallLizardStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x243);
    char *c;
    char *w;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x210, 0x10);
    *(char **)(c + 0x1200) = w;
    CharaCtrlResetCtrlStatus(th);
    *(int *)(w + 0x40) = getEditWorkInitData(*(int *)(GetScriptClass(th) + 0x40));
    while ((*(void **)(w + 0x44) = SCRGetFirstObj(gcGlobalVar + 0x2B0)) == 0)
        scrRun();
    AI_InitAnimalWork(w, 2);
    func_000B2890(w);
    isysJumpSubThread(func_000B1D88, w);
}
