extern int *DldSysUndefSymbol;
extern int isysGetThisSubThread(void);
extern char *GetScriptClass(int);
extern int AI_GetCurMotionKind(int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static int func_0009F308(void)
{
    int th = isysGetThisSubThread();
    unsigned int *a = *(unsigned int **)(GetScriptClass(th) + 0x48);
    unsigned int v = *a;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)a - off) : 0;
    unsigned int *x = (t != 0 && t != DldSysUndefSymbol) ? (unsigned int *)t[4] : 0;
    char *y;
    int s;

    if (x != 0 && (y = dldResolve(x)) != 0) {
        s = (int)dldResolve((unsigned int *)(y + 4));
        if (s == AI_GetCurMotionKind(th))
            return 1;
    }
    return 0;
}
