extern int fsEffectManagerInit();

int setDefaultFsEffect(int a, int b, int c, int d)
{
    return fsEffectManagerInit(a, b, c, d);
}
