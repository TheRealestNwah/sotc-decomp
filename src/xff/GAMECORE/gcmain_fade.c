extern char rootPtn[];
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);
extern void D_0000C5A0(void);
extern void D_0000C538(void);
extern void D_0000C5F0(void);
extern int D_00179F14;
typedef union {
    struct {
        float start;
        float end;
        float from;
        float to;
        float cur;
        int kind;
    } s;
    char alias;
} FadeParam;
extern FadeParam D_00179F00;
extern void setFadeParam(FadeParam *, int, float, float);
extern int checkFadeParam(float *);
extern float D_00179F10;
extern unsigned char D_00179F30[];
extern char D_00179F18[];
extern void SetDefaultGameAnimeTimeScaleRatio(float);
extern void RestoreDefaultGameAnimeTimeScaleRatio(float);
extern float GetGameAnimeTimeScaleRatio(void);
extern void ChangeGameAnimeTimeScaleRatio(float, float);
extern float D_00179F28;
extern char gcGlobalVar[];
extern long iosGetTCountExtension(void);
extern void graphFrameInit(float);
extern void InitLayoutObjMatrix(int);
extern void scrRun(void);
extern void calcFadeParam(void *);
extern void setFadeLayer(int);
extern void fadeScreen(float);
extern void drawDemoBar(int, int, float);
extern void graphFrameFinish(void);
extern void windowDraw(void);
extern void InitLightColMan(void);
extern void CreateLightColMan(void *);
extern void TaskExecLightColMan(void);

static void func_0000C4E8(void);

void initgcmaingp(void)
{
    gcCreateScriptObj(func_0000C4E8, 0, rootPtn, 0x1000, 0, 1, "st_gpframeinit");
    gcCreateScriptObj(D_0000C5A0, 0, rootPtn, 0x2000, 0, 10, "st_windowdraw");
    gcCreateScriptObj(D_0000C538, 0, rootPtn, 0x1000, 0, 11, "st_gpframefinish");
    gcCreateScriptObj(D_0000C5F0, 0, rootPtn, 0x1000, 0, 2, "st_lightcolman");
}

void setLayerFade(int value)
{
    D_00179F14 = value;
}

void setFade(float to, float time)
{
    setFadeParam(&D_00179F00, 27, to, time);
}

int getFade(void)
{
    return checkFadeParam((float *)((unsigned char *)&D_00179F00));
}

float getFadeValue(void)
{
    return D_00179F10;
}

void setFadeValue(float fparg0)
{
    D_00179F10 = fparg0;
}

void *getDemoBarSw(void)
{
    return D_00179F30;
}

void setDemoBar(float a, float b)
{
    if (a != 0.0f) {
        SetDefaultGameAnimeTimeScaleRatio(1.0f);
        ChangeGameAnimeTimeScaleRatio(GetGameAnimeTimeScaleRatio(), 0.0f);
    } else {
        RestoreDefaultGameAnimeTimeScaleRatio(1.0f);
        ChangeGameAnimeTimeScaleRatio(GetGameAnimeTimeScaleRatio(), 0.0f);
    }
    setFadeParam(D_00179F18, 0x18, a, b);
}

int getDemoBar(void)
{
    return checkFadeParam((float *)((unsigned char *)&D_00179F18));
}

float getDemoBarFade(void)
{
    return 1.0f - D_00179F28;
}

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

static void T_0000C538(void)
{
    char *a = ((char *)&D_00179F00);
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

static void T_0000C5F0(void)
{
    InitLightColMan();
    CreateLightColMan(rootPtn);
    for (;;) {
        TaskExecLightColMan();
        scrRun();
    }
}
