typedef struct {
    char p0[0x70];
    long t70;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern long iosGetTCountExtension(void);
extern void *GetScriptPriorityGroup(int);
extern void func_0000AA90(void *);
extern void updatePathInfo(void);
extern void scrRun(void);

static void func_0000B4E0(void)
{
    void *group = GetScriptPriorityGroup(4);

    for (;;) {
        func_0000AA90(group);
        updatePathInfo();
        gcGlobalVar.t70 = iosGetTCountExtension();
        scrRun();
    }
}
