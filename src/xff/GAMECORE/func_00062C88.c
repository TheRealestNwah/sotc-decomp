extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void updateScriptDataSystem(void *);
extern void scrRunM(int);

static void func_00062C88(int *w)
{
    isysGetThisSubThread();

    while (1) {
        void *t = isysGetThisSubThread();

        SCRExecBossPreProcess(*w);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateScriptDataSystem(t);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*w);
        scrRunM(1);
    }
}
