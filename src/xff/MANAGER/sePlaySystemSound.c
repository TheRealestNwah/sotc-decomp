extern int *DldSysUndefSymbol;
static void func_000DD938(void);
extern char *sndSepReq(void *, void *, int, int, int, int, int);

static inline char *sepReq(void *f1, void *f2, int u, int id)
{
    if (id == u)
        return 0;
    return sndSepReq(f1, f2, 0, id, 0, 1, 0);
}

char *sePlaySystemSound(int id)
{
    return sepReq(func_000DD938, 0, *DldSysUndefSymbol, id);
}
