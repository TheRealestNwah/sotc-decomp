extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void updateScriptDataSystem(void *);
extern void scrRunM(int);

static void func_000CA9F0(char *w)
{
    isysGetThisSubThread();

    while (1) {
        void *t = isysGetThisSubThread();

        SCRExecBossPreProcess(*(int *)w);
        CharaCtrlResetAllScriptCtrlStatus(t);
        updateScriptDataSystem(t);
        *(long long *)(w + 0x41B8) = 0;
        isysGetThisSubThread();
        SCRExecBossPostProcess(*(int *)w);
        scrRunM(1);
    }
}
