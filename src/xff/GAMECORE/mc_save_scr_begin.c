extern int *DldSysUndefSymbol;
extern char *GetLayoutClass(void *);
extern void bootMemoryCardSaveScriptNoBlock(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = 0;

    if (off != 0)
        t = *(int **)((char *)h - off);
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline char *dldResolveRe(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((*h >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void mc_save_scr_begin(void *obj)
{
    char *g = obj != 0 ? *(char **)(GetLayoutClass(obj) + 0x1A4) : 0;
    char *p = 0;

    if (g != 0)
        p = dldResolveRe((unsigned int *)dldResolve((unsigned int *)(g + 0x10)));
    bootMemoryCardSaveScriptNoBlock(p);
}
