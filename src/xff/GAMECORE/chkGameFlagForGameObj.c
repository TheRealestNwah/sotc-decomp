extern int *DldSysUndefSymbol;
extern char *GetLayoutClass(void *);
extern int gStatGobjDispGflagChk(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

int chkGameFlagForGameObj(void *obj)
{
    char *g = GetLayoutClass(obj) != 0 ? *(char **)(GetLayoutClass(obj) + 0x1A4) : 0;

    if (dldResolve((unsigned int *)(g + 0x10)) != 0) {
        return gStatGobjDispGflagChk(dldResolve((unsigned int *)(g + 0x10)));
    }
    return 0;
}
