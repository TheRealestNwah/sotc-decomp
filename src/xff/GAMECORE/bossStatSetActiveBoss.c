extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern void _gameFlagCls(int);
extern void _gameFlagSet(int);
extern void _gameWorkSet(int, int);
extern void setBossClearCnt(int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int *bossSheet(void)
{
    return DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
}

void bossStatSetActiveBoss(char *boss)
{
    int *sh = bossSheet();
    char *e = (char *)sh[4];
    int i;

    for (i = 0; i < sh[3]; i++) {
        int flag = *(int *)(dldResolve((unsigned int *)(e + 0x24)) + 0xC);

        if (boss == e)
            _gameFlagCls(flag);
        else
            _gameFlagSet(flag);
        e += 0xEC;
    }
    if (boss == 0) {
        _gameWorkSet(8, -1);
        setBossClearCnt(0);
        return;
    }
    {
        int n = (unsigned int)(boss - (char *)bossSheet()[4]) / 0xEC;

        _gameWorkSet(8, n);
        setBossClearCnt(n);
    }
    _gameFlagSet(*(int *)(boss + 0x18));
    {
        int *s = DldSysUndefSymbol == SH_BossStatusDEFAULT ? 0 : SH_BossStatusDEFAULT;
        char *p = (char *)s[4];
        int n = s[3];
        int j;

        for (j = 0; j < n; j++) {
            if (*(int *)(p + 0x20) != 0)
                _gameFlagCls(*(int *)(p + 0x20));
            p += 0xEC;
        }
    }
}
