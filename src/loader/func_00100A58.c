extern int GetThreadId(void);
extern int ChangeThreadPriority(int thread, int priority);
extern void sceSifInitRpc(int mode);
extern int sceSifInitIopHeap(void);
extern int CancelWakeupThread(int thread);
extern int WakeupThread(int thread);
extern int SleepThread(void);
extern void PutString(int attr, const char *format, ...);
extern int LoaderSysPrintf(const char *format, ...);
extern void LoaderSysSendAbort(void);
extern void loaderExecResetCallback(void);
extern int padSysReadForLoader(void);
extern int ExecBaseProc(void);
extern void Sync(void);
extern void loaderLoop(void);
extern char D_00139E50[];
extern char D_00136320[];
extern char D_0013B348[];
extern char D_00136338[];
extern char D_00136378[];
extern int D_0013A080;
extern int D_0013A084;

void func_00100A58(void) {
    register int sp asm("$29");
    int id;
    int pad;
    int t;
    unsigned int *p;

    id = GetThreadId();
    if (id == D_0013A084) {
        ChangeThreadPriority(GetThreadId(), 1);
        sceSifInitRpc(0);
        sceSifInitIopHeap();
        /* Restore the loader gp/sp; t is passed in so its load stays before the reload. */
        t = D_0013A084;
        __asm__ volatile("la $gp, _gp" :: "r"(t));
        sp = D_0013A080;
        CancelWakeupThread(t);
        WakeupThread(D_0013A084);
        /* Patch the jal below (through the uncached mirror) to jump into loaderLoop. */
        __asm__ volatile("la %0, D_00100AF4" : "=r"(p));
        p = (unsigned int *)((unsigned int)p | 0x20000000);
        *p = (*p & 0xFF000000) | ((unsigned int)loaderLoop >> 2);
        __asm__ volatile("D_00100AF4:\n\tjal func_0\n\tnop");
    }
    ChangeThreadPriority(id, 0x7F);
    PutString(0xFF603000, D_00139E50);
    PutString(0xFF603000, D_00136320, id);
    PutString(0xFF603000, D_0013B348);
    PutString(0xC0FFE000, D_00136338);
    PutString(0xC0FFE000, D_00136378);
    LoaderSysPrintf(D_00139E50);
    LoaderSysSendAbort();
    loaderExecResetCallback();
    while (1) {
        pad = padSysReadForLoader();
        ExecBaseProc();
        if (pad & 0x800) break;
        Sync();
    }
    PutString(0xFF603000, D_00139E50);
    ChangeThreadPriority(GetThreadId(), 0x7F);
    WakeupThread(D_0013A084);
    for (;;) {
        SleepThread();
    }
}
