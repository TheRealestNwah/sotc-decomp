extern void __main(void);
extern int printf(const char *format, ...);
extern char *strncpy(char *dst, const char *src, unsigned int n);
extern int GetThreadId(void);
extern void InitDisp(void);
extern void initmemprintf(int start, int end);
extern void func_001033B0(void);
extern void InitException(void);
extern void LoaderSysInitExternalIntcHandlerList(void);
extern void LoaderSysInitExternalThreadList(void);
extern void LoaderSysInitExternalSemaList(void);
extern void LoaderSysInitExternalIopMemoryList(void);
extern int ChangeThreadPriority(int thread, int priority);
extern void PutStringS(int attr, const char *format, ...);
extern void loaderLoop(void);
extern char D_00136D88[];
extern char D_00136DA0[];
extern char D_00136DB8[];
extern char D_0013CF90[16];
extern int D_0013A010;
extern int D_0013A080;
extern int D_0013A084;

int func_00103B40(int argc, char **argv) {
    register char *sp asm("$29");
    int i;
    char *end;
    int size;

    __main();
    printf(D_00136D88, argc);
    for (i = 0; i < argc; i++) {
        printf(D_00136DA0, i, argv[i]);
    }
    if (argc != 0) {
        strncpy(D_0013CF90, argv[0], 0x10);
        D_0013CF90[15] = 0;
    } else {
        D_0013CF90[0] = 0;
    }
    D_0013A084 = GetThreadId();
    InitDisp();
    initmemprintf(0x2000000, 0x7FFFF00);
    func_001033B0();
    __asm__ volatile("lui %0, %%hi(D_16A398)\n\tnop\n\taddiu %0, %0, %%lo(D_16A398)\n\tnop" : "=r"(end));
    __asm__ volatile("lui %0, %%hi(D_40000)\n\tnop\n\taddiu %0, %0, %%lo(D_40000)\n\tnop" : "=r"(size));
    D_0013A010 = ((int)end + size + 0xF) & ~0xF;
    InitException();
    LoaderSysInitExternalIntcHandlerList();
    LoaderSysInitExternalThreadList();
    LoaderSysInitExternalSemaList();
    LoaderSysInitExternalIopMemoryList();
    ChangeThreadPriority(D_0013A084, 1);
    PutStringS(-0x100, D_00136DB8);
    D_0013A080 = (int)sp;
    loaderLoop();
    return 0;
}
