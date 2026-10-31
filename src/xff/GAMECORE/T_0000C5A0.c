extern char gcGlobalVar[];
extern long iosGetTCountExtension(void);
extern void windowDraw(void);
extern void scrRun(void);

static void T_0000C5A0(void)
{
    char *g = gcGlobalVar;
    long e = 0;
    long s = 0;

    for (;;) {
        *(long *)(g + 0xE8) = e;
        *(long *)(g + 0xE0) = s;
        s = iosGetTCountExtension();
        windowDraw();
        e = iosGetTCountExtension();
        scrRun();
    }
}
