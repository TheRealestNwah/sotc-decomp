struct ProgInfo {
    char unk0[0x10];
    void (*entry)(int argc, char **argv);
};

extern int GetThreadId(void);
extern struct ProgInfo *func_00100D48(void *arg);
extern void FlushCache(int op);
extern int LoaderSysPrintf(const char *format, ...);
extern void PutStringS(int attr, const char *format, ...);
extern void LoaderSysDeleteExternalThreadList(int thread);
extern void ExitDeleteThread(void);
extern int D_00139E00;
extern int D_00139E04;
extern struct ProgInfo *D_00131C44[];
extern char D_00136508[];
extern char D_001363D0[];

void _execProgWithThread(void *arg) {
    int thread = GetThreadId();
    struct ProgInfo *info = func_00100D48(arg);

    if (info != 0) {
        void (*entry)(int argc, char **argv);
        register char **argv __asm__("$16");

        D_00131C44[0] = info;
        entry = info->entry;
        D_00139E00 = D_00139E04;
        __asm__ volatile("lui %0, %%hi(D_00131BAC)\n\tnop\n\taddiu %0, %0, %%lo(D_00131BAC)\n\tnop" : "=r"(argv));
        FlushCache(0);
        FlushCache(2);
        LoaderSysPrintf(D_001363D0, entry, argv);
        entry(1, argv);
    } else {
        PutStringS(0xFF804000, D_00136508);
    }
    LoaderSysDeleteExternalThreadList(thread);
    ExitDeleteThread();
}

