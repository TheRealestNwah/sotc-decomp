extern int DldSysUndefSymbol;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline int *dldObj(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
}

extern char *GetCharacterClass(void *);

int SCRConditionGameObjMotionShiftCheck(void *a, int b, int c, int d, int e, int f, int g, int *h1, unsigned int *h2)
{
    int none;
    int *o = dldObj(h1);
    char *m;
    int ret;

    if (o == 0 || o[2] == 0)
        return 0;
    none = GetCharacterClass((void *)o[2]) == 0;
    if (none)
        return 0;
    m = GetCharacterClass((void *)o[2]) + 0x1C0;
    ret = 0;
    if (dldResolve(h2) == *(char **)(m + 0))
        ret = *(signed char *)(GetCharacterClass((void *)o[2]) + 0x360) != 0;
    return ret;
}
