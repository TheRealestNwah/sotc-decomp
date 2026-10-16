extern int *DldSysUndefSymbol;
extern char *GetLayoutClass(void *);
extern void gameflowSetPauseEnable(int);
extern void *SCRGetGetGeometryPointerLegalParentObj(void *);
extern void gStatGobjDispGflagSet(void *);
extern int getGameHardMode(void);
extern void _omakeGetFlagSet(int);
extern void func_00070978(void);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline char *dldResolveRe(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((*h >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void nico_setOmakeItemFlag(void *obj)
{
    char *c = GetLayoutClass(obj);
    char *g;
    unsigned int *s;
    int *it;
    int f;

    gameflowSetPauseEnable(0);
    g = GetLayoutClass(SCRGetGetGeometryPointerLegalParentObj(c + 0xC0));
    s = (unsigned int *)dldResolve((unsigned int *)(*(char **)(g + 0x1A4) + 0x10));
    gStatGobjDispGflagSet(s);
    it = (int *)dldResolveRe(s);
    if (getGameHardMode())
        f = it[2];
    else
        f = it[0];
    if (f != 0) {
        _omakeGetFlagSet(f);
        func_00070978();
    }
}
