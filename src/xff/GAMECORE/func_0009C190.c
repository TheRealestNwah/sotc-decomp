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

static int func_0009C190(void)
{
    void *thread = isysGetThisSubThread();
    unsigned int *base = (unsigned int *)dldBase(*(unsigned int **)(GetScriptClass(thread) + 0x48));

    if (base != 0) {
        unsigned int *e = (unsigned int *)dldResolve(base);

        if (e != 0) {
            char *k = dldResolve(e);

            if (k == AI_GetCurMotionKind(thread))
                return 1;
        }
    }
    return 0;
}
