extern char B_000C5C18[];
extern int B_000D9218;
extern void *memset(void *p, int c, unsigned int n);
extern void func_00021488(int id);
extern void Sg2ModTickProc(void);
extern int Sg2CtrlEntryTickProcById(int id, void (*proc)(void));

int Sg2ModInit(int reserved)
{
    char *p = B_000C5C18;
    int i;

    for (i = 0; i < 0x20; i++) {
        memset(p, 0, 0x9B0);
        p += 0x9B0;
        func_00021488(i);
    }
    B_000D9218 = 1;
    Sg2CtrlEntryTickProcById(2, Sg2ModTickProc);
    return 0;
}
