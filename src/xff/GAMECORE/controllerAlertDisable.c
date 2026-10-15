extern volatile int D_0017A9A8;

void controllerAlertDisable(int on)
{
    volatile int *p = &D_0017A9A8;
    if (on == 1)
        *p += 1;
    else
        *p -= 1;
    if (D_0017A9A8 < 0)
        D_0017A9A8 = 0;
}
