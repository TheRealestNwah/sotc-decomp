extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void CharaCtrlSetOutsideScriptCtrlStatus(void *, int);
extern void updateScriptDataSystem(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetCharacterClass(void *);
extern void func_0006DEA8(void *);
extern void scrRunM(int);
extern char *GameObject_NARGA_HEAD;
extern char *ScriptCtrlDef_SCRNargaMouthClose;

static void func_0006E098(int *w)
{
    void *th = isysGetThisSubThread();

    while (1) {
        void *t = isysGetThisSubThread();
        char *work;

        SCRExecBossPreProcess(*w);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateScriptDataSystem(t);
        work = getSCRDataCtrlWork(th);
        if (*(int *)(GetCharacterClass(th) + 0x750) != *(int *)(work + 0x4170)) {
            CharaCtrlSetOutsideScriptCtrlStatus(*(void **)(GameObject_NARGA_HEAD + 8),
                                                *(int *)(ScriptCtrlDef_SCRNargaMouthClose + 4));
        } else {
            CharaCtrlResetAllScriptCtrlStatus(*(void **)(GameObject_NARGA_HEAD + 8));
        }
        func_0006DEA8(th);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*w);
        scrRunM(1);
    }
}
