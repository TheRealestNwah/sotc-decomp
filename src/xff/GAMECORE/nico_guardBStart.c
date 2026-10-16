extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern void scrRunM(int);
extern int ScriptCtrlDef_SCRGuardBDamageFront;
extern int ScriptCtrlDef_SCRGuardBDamageBack;
extern void func_00056408(char *);
extern void func_00056740(void);

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
