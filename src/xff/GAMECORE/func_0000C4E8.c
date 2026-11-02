extern char gcGlobalVar[];
extern long iosGetTCountExtension(void);
extern void graphFrameInit(float);
extern void InitLayoutObjMatrix(int);
extern void scrRun(void);

static void func_0000C4E8(void)
{
    char *g = gcGlobalVar;

    for (;;) {
        *(long *)(g + 0x80) = iosGetTCountExtension();
        graphFrameInit(*(float *)(g + 0x180));
        InitLayoutObjMatrix(*(int *)(g + 0x1AC));
        *(long *)(g + 0x88) = iosGetTCountExtension();
        scrRun();
    }
}
