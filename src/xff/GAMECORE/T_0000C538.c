extern char D_00179F00[];
extern char D_00179F18[];
extern void calcFadeParam(void *);
extern void setFadeLayer(int);
extern void fadeScreen(float);
extern void drawDemoBar(int, int, float);
extern void graphFrameFinish(void);
extern void scrRun(void);

static void T_0000C538(void)
{
    char *a = D_00179F00;
    char *b = D_00179F18;

    for (;;) {
        calcFadeParam(a);
        setFadeLayer(*(int *)(a + 0x14));
        fadeScreen(*(float *)(a + 0x10));
        calcFadeParam(b);
        drawDemoBar(0x1B, 0x40, *(float *)(b + 0x10));
        graphFrameFinish();
        scrRun();
    }
}
