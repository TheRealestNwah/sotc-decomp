extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int _gameFlagChk(int);
extern void SCRSetDispFlag(int, int);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol)
               ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)
               : 0;
}

void bossStatInitCloudLayout(void)
{
    int *sh = DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    char *e = (char *)sh[4];
    int n = sh[3];
    int i;

    for (i = 0; i < n; i++) {
        char *l = dldElem((unsigned int *)(e + 0x10));

        if (l != 0) {
            char *c = dldElem((unsigned int *)(l + 4));

            if (_gameFlagChk(*(int *)(e + 0x18)))
                SCRSetDispFlag(*(int *)(c + 8), 0);
            else
                SCRSetDispFlag(*(int *)(c + 8), 1);
        }
        e += 0xEC;
    }
}
