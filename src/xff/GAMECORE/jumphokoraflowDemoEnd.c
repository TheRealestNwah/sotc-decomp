extern int jumphokoraFlag[];

void jumphokoraflowDemoEnd(int a)
{
    int *f = jumphokoraFlag;

    f[1] = a;
    f[0] |= 2;
}
