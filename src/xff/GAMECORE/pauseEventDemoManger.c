extern int D_0017B8B8;

void pauseEventDemoManger(int on)
{
    int *p = &D_0017B8B8;
    int v;

    if (on == 1)
        v = *p + 1;
    else
        v = *p - 1;
    *p = v;
}
