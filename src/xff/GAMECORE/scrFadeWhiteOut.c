extern int ScrIntrDef_SCREEN_FADEOUT;
extern int D_0017A024, D_0017A020;
extern float D_0017A01C;
extern void setFadeColor(int);
extern void setFadeValue(float);
extern void scriptIntrSignal(int);

void scrFadeWhiteOut(float t)
{
    setFadeColor(1);
    if (t == 0.0f) {
        setFadeValue(1.0f);
        return;
    }
    D_0017A024 = 1;
    D_0017A020 = 100;
    D_0017A01C = t;
    scriptIntrSignal(ScrIntrDef_SCREEN_FADEOUT);
    t = 0;
}
