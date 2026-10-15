extern int ScrIntrDef_SCREEN_FADEIN;
extern int D_0017A024, D_0017A020;
extern float D_0017A01C;
extern void setFadeValue(float);
extern void scriptIntrSignal(int);

void scrFadeIn(float t)
{
    if (t == 0.0f) {
        setFadeValue(0.0f);
        return;
    }
    D_0017A024 = 7;
    D_0017A020 = 200;
    D_0017A01C = t;
    scriptIntrSignal(ScrIntrDef_SCREEN_FADEIN);
    t = 0;
}
