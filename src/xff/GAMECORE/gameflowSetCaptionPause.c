extern int D_0017A088;
extern void SetCaptionPauseFlag(int);

void gameflowSetCaptionPause(int on)
{
    int *p = &D_0017A088;
    int n = *p;
    int m = on == 1 ? n + 1 : n - 1;
    *p = m;
    if (n > 0 && m == 0)
        SetCaptionPauseFlag(0);
    else if (n == 0 && D_0017A088 > 0)
        SetCaptionPauseFlag(1);
}
