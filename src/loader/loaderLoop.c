extern void *malloc(unsigned int size);
extern void free(void *p);
extern void PutStringS(int attr, const char *format, ...);
extern void *memset(void *dst, int c, unsigned int n);
extern void SetHeapStartPoint(int p);
extern int execProgWithThread(const char *name, int prio);
extern int SleepThread(void);
extern void LoaderSysExecuteRecoveryFirstProcess(void);
extern int ChangeThreadPriority(int thread, int priority);
extern void LoaderSysDeleteAllExternalIntcHandler(void);
extern void LoaderSysDeleteAllExternalThread(void);
extern void LoaderSysDeleteAllExternalSema(void);
extern void LoaderSysDeleteAllExternalIopMemory(void);
extern void ReinitDisp(void);
extern char D_00136CD0[];
extern char D_00136CE0[];
extern char D_00136CF0[];
extern char D_00136D00[];
extern char D_00136D10[];
extern char D_00136D60[];
extern char D_00136D78[];
extern char D_16A398[];
extern void (*D_0013CFA0[10])(void);
extern int D_0013A010;
extern int D_0013A014;
extern int D_0013A07C;
extern int D_0013A084;

void loaderLoop(void) {
    register char *gp asm("$28");
    register char *sp asm("$29");
    int count = 0;
    void *p;
    int i;

    p = malloc(1);
    free(p);
    PutStringS(-0x100, D_00136CD0, gp);
    PutStringS(-0x100, D_00136CE0, sp);
    PutStringS(-0x100, D_00136CF0, p);
    PutStringS(-0x100, D_00136D00, (long)D_16A398);
    PutStringS(-0x100, D_00136D10, D_0013A010);
    memset(D_0013CFA0, 0, sizeof(D_0013CFA0));
    D_0013A07C = 0;
    while (1) {
        SetHeapStartPoint(D_0013A010);
        D_0013A014 = execProgWithThread(D_00136D60, 2);
        SleepThread();
        for (i = 0; i < 10; i++) {
            if (D_0013CFA0[i]) D_0013CFA0[i]();
        }
        count++;
        memset(D_0013CFA0, 0, sizeof(D_0013CFA0));
        D_0013A07C = 0;
        LoaderSysExecuteRecoveryFirstProcess();
        ChangeThreadPriority(D_0013A084, 1);
        LoaderSysDeleteAllExternalIntcHandler();
        LoaderSysDeleteAllExternalThread();
        LoaderSysDeleteAllExternalSema();
        LoaderSysDeleteAllExternalIopMemory();
        ReinitDisp();
        PutStringS(-0x100, D_00136D78, count);
    }
}
