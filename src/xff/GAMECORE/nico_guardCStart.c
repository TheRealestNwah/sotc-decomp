extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern int ScriptCtrlDef_SCRGuardCDamageFront;
extern int ScriptCtrlDef_SCRGuardCDamageBack;
extern void func_00055780(char *);
extern void func_00055580(void);

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
