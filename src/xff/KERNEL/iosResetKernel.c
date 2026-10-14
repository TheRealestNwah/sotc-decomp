extern int LoaderSysResetSystem();

int iosResetKernel(int a, int b, int c, int d)
{
    return LoaderSysResetSystem(a, b, c, d);
}
