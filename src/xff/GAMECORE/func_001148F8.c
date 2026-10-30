extern int *DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void);
extern float iosGetRandom(void);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static void func_001148F8(void)
{
    char **work = (char **)(getSCRDataCtrlWork() + 0x40C0);
    char *entry = work[1];
    int go;

    if (entry == 0)
        return;
    if (dldResolve((unsigned int *)(entry + 4)) == 0)
        return;
    go = 1;
    if (*(float *)(entry + 8) < 100.0f && *(float *)(entry + 8) < iosGetRandom() * 100.0f)
        go = 0;
    if (go)
        work[0] = dldResolve((unsigned int *)(entry + 4));
}
