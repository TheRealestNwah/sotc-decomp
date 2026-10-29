extern int ScrIntrDef_SCREEN_FADEOUT;
extern int D_0017A024, D_0017A020;
extern float D_0017A01C;
extern void setFadeValue(float);
extern void setFadeColor(int);
extern void scriptIntrSignal(int);
extern int PauseGame(int);
extern void scrRun(void);

static inline void doFadeOut(int wait, int pause, float t)
{
    if (t == 0.0f) {
        setFadeValue(1.0f);
        return;
    }
    D_0017A024 = 1;
    D_0017A020 = 100;
    D_0017A01C = t;
    scriptIntrSignal(ScrIntrDef_SCREEN_FADEOUT);
    if (wait != 0) {
        while (D_0017A020 != 0)
            scrRun();
        if (pause != 0)
            PauseGame(1);
    }
}

void fadeOut(int wait, int pause, float t)
{
    setFadeColor(0);
    doFadeOut(wait, pause, t);
}
