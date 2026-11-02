extern void LoaderSysExecuteRecoveryFirstProcess(void);
extern void PutString(int attr, const char *format, ...);
extern int GetThreadId(void);
extern int ChangeThreadPriority(int thread, int priority);
extern int WakeupThread(int thread);
extern int SleepThread(void);
extern char D_00139E50[];
extern int D_0013A084;

void LoaderSysResetSystem(void) {
    LoaderSysExecuteRecoveryFirstProcess();
    PutString(0xFF603000, D_00139E50);
    ChangeThreadPriority(GetThreadId(), 0x7F);
    WakeupThread(D_0013A084);
    for (;;) {
        SleepThread();
    }
}
