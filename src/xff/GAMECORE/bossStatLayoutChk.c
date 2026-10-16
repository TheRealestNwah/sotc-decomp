extern int *DldSysUndefSymbol;
extern int _gameFlagChk(int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

int bossStatLayoutChk(char *b)
{
    return _gameFlagChk(*(int *)(dldResolve((unsigned int *)(b + 0x24)) + 0xC)) == 0;
}
