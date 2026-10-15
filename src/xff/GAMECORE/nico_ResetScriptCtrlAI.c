extern void *isysGetThisSubThread(void);

extern void CharaCtrlResetAllScriptCtrlStatus(void *thread);

extern void scrRun(void);

void nico_ResetScriptCtrlAI(void)
{
    for (;;) {
        CharaCtrlResetAllScriptCtrlStatus(isysGetThisSubThread());
        scrRun();
    }
}
