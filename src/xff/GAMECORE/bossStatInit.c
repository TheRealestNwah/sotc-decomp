extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int SH_GameObjectStatusDEFAULT[];
extern void func_0000FF60(int *);
extern void _gameWorkSet(int, int);
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);
extern void setBossClearCnt(int);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol)
               ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)
               : 0;
}

void bossStatInit(void)
{
    int *sh;
    char *e;
    int i;

    func_0000FF60(DldSysUndefSymbol != SH_GameObjectStatusDEFAULT ? SH_GameObjectStatusDEFAULT : 0);
    _gameWorkSet(8, -1);
    sh = DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    e = (char *)sh[4];
    for (i = 0; i < sh[3]; i++) {
        char *c = dldElem((unsigned int *)(e + 0x24));

        int flag = *(int *)(c + 0xC);

        if (e == 0)
            _gameFlagCls(flag);
        else
            _gameFlagSet(flag);
        e += 0xEC;
    }
    setBossClearCnt(0);
}
