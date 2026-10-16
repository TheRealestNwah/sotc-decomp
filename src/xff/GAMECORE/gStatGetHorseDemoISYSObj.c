typedef struct {
    int a;
    int flag;
    int stage;
    unsigned int obj;
    int set;
} HorseType;

extern int DldSysUndefSymbol;
extern int SH_HorseTypeDEFAULT[];
extern int _omakeSelectFlagChk(int);

static inline HorseType *findHorse(void)
{
    int *sh = SH_HorseTypeDEFAULT;
    int n = sh[3];
    HorseType *e = (HorseType *)sh[4];
    HorseType *base = e;
    int i;

    n--;
    e++;

    for (i = 0; i < n; i++, e++) {
        if (_omakeSelectFlagChk(e->flag))
            return e;
    }
    return base;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

int gStatGetHorseDemoISYSObj(void)
{
    char *p = dldResolve(&findHorse()->obj);
    int r = 0;

    if (p != 0)
        r = *(int *)(p + 8);
    return r;
}
