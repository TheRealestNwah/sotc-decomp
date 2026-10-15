extern int *DldSysUndefSymbol;
static void func_000DD938(void);
static void func_000DDD28(void);
extern char *sndSepReq(void *, void *, int, int, int, int, int);

static inline char *sepReq(void *f1, void *f2, int u, int id)
{
    if (id == u)
        return 0;
    return sndSepReq(f1, f2, 0, id, 0, 2, 0);
}

char *sePlayStageEnv(int id, int val)
{
    char *s = sepReq(func_000DD938, func_000DDD28, *DldSysUndefSymbol, id);
    if (s == 0)
        return 0;
    *(int *)(s + 0x3C) = val;
    return s;
}
