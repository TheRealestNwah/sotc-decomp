void SetScrLwsOriObjReleaseCallBackFunc(unsigned char *p, int a, int b)
{
    char *c = p[8] != 0x16 ? 0 : (char *)p + 0x20;
    int *f = (int *)(c + 0x120C);

    f[0] = a;
    f[1] = b;
}
