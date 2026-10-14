extern int D_001303E0[];
extern int fsEffectDefault();

int effectReset(void)
{
    int *p = D_001303E0;

    p[0] = 0;
    p[1] = 0;
    return fsEffectDefault();
}
