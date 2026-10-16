extern char D_00179F18[];
extern void SetDefaultGameAnimeTimeScaleRatio(float);
extern void RestoreDefaultGameAnimeTimeScaleRatio(float);
extern float GetGameAnimeTimeScaleRatio(void);
extern void ChangeGameAnimeTimeScaleRatio(float, float);
extern void setFadeParam(void *, int, float, float);

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
