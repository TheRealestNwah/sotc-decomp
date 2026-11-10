#ifdef NONMATCHING
/* 74 diffs, same length. Third sibling of func_000AE5E8 / func_000AE758 (those match): entry = resolve(base), then two more refs at entry+4 and entry+8 are resolved and compared with AI_GetCurMotionKind. Returns 1 when either ref equals the current kind. Difference: the Original passes the first resolve result through $v0 before moving it to $a2 (an extra move, which shifts every later branch offset); ours writes $a2 directly. Permuter (10 workers, 25 min): best 1940 only. */
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

static int func_000AE8C0(void)
{
    void *thread = isysGetThisSubThread();
    char *base = dldBase(*(unsigned int **)(GetScriptClass(thread) + 0x48));
    char *entry = base != 0 ? dldResolve((unsigned int *)base) : 0;
    char *a;
    char *b;
    char *cur;

    if (entry == 0)
        return 0;
    a = dldResolve((unsigned int *)(entry + 4));
    b = dldResolve((unsigned int *)(entry + 8));
    cur = AI_GetCurMotionKind(thread);
    if (a != 0 && cur != 0 && a == cur)
        return 1;
    if (b != 0 && cur != 0 && b == cur)
        return 1;
    return 0;
}
#endif
