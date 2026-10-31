typedef struct {
    char p0[0x78];
    long t78;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;
extern long iosGetTCountExtension(void);
extern void scrRun(void);

static void T_0000B530(void)
{
    for (;;) {
        gcGlobalVar.t78 = iosGetTCountExtension();
        scrRun();
    }
}
