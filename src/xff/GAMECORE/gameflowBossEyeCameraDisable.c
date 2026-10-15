extern volatile int D_0017A074;

void gameflowBossEyeCameraDisable(int on)
{
    volatile int *p = &D_0017A074;
    if (on == 1)
        *p += 1;
    else
        *p -= 1;
    if (D_0017A074 < 0)
        D_0017A074 = 0;
}
