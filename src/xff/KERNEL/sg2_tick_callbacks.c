typedef struct {
    void (*func)(void);
    int count;
} Ctrl;
extern Ctrl B_000C5A80[];
extern void func_0001F6C8(void);
extern int DIntr(void);
extern int EIntr(void);
extern int Sg2CtrlEntryTickProcById(int, void (*)(void));
int Sg2CtrlEntryTickProc(void (*proc)(void))
{
    int result = -1;
    int enabled = DIntr();
    int i;
    for (i = 0; i < 16; ++i) {
        if (B_000C5A80[i].func == func_0001F6C8) {
            Sg2CtrlEntryTickProcById(i, proc);
            result = 0;
            break;
        }
    }
    if (enabled)
        EIntr();
    return result;
}
int Sg2CtrlRemoveTickProc(void (*proc)(void))
{
    int result = -1;
    int enabled = DIntr();
    int i;
    for (i = 0; i < 16; ++i) {
        if (B_000C5A80[i].func == proc) {
            B_000C5A80[i].func = func_0001F6C8;
            B_000C5A80[i].count = 0;
            result = 0;
            break;
        }
    }
    if (enabled)
        EIntr();
    return result;
}