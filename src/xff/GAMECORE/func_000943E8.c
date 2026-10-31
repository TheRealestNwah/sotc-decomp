extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void updateScriptDataSystem(void *);
extern void scrRunM(int);

static void func_000943E8(int *boss)
{
    isysGetThisSubThread();
    for (;;) {
        void *th = isysGetThisSubThread();

        SCRExecBossPreProcess(*boss);
        CharaCtrlResetAllScriptCtrlStatus(th);
        updateScriptDataSystem(th);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*boss);
        scrRunM(1);
    }
}
