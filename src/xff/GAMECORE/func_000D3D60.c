extern int DldSysUndefSymbol;
extern short *getAnimObjResource(char *);

static inline int dldCount(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static float func_000D3D60(char *p, int *count)
{
    float total = 0.0f;
    int n = dldCount((unsigned int *)(p + 4));
    char *e = dldResolve((unsigned int *)(p + 4));

    *count = n;
    while (n--) {
        char *r = dldResolve((unsigned int *)(e + 4));

        e += 0x30;
        total += getAnimObjResource(r + 4)[2];
    }
    return total * (1.0f / 30.0f);
}
