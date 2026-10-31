extern int *DldSysUndefSymbol;
extern void *isysGetThisSubThread(void);
extern char *GetScriptClass(void *);
extern char *AI_GetCurMotionKind(void *);

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static int func_000AE5E8(void)
{
    void *thread = isysGetThisSubThread();
    char *base = dldBase(*(unsigned int **)(GetScriptClass(thread) + 0x48));
    char *entry = base != 0 ? dldResolve((unsigned int *)base) : 0;
    char *kind;
    char *cur;

    do {
        if (entry == 0)
            return 0;
        kind = dldResolve((unsigned int *)(entry + 0x10));
        cur = AI_GetCurMotionKind(thread);
        if (kind != 0 && cur != 0 && kind == cur)
            return 1;
        return 0;
    } while (0);
}
