extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern void _gameFlagSet(int);

static inline int *dldPtr(unsigned int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol)
               ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)
               : 0;
}

static void func_0000FF60(int *sh)
{
    unsigned int *e = (unsigned int *)sh[4];
    int i;

    for (i = 0; i < sh[3]; i++, e += 5) {
        int *t = dldPtr(e);
        int *cls = (t != 0 && t != DldSysUndefSymbol) ? t : 0;

        if (cls == (DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0)) {
            char *c = dldElem(e);

            if (e[1] == 0x303) {
                *(unsigned int **)(c + 0xE8) = e;
                _gameFlagSet(*(int *)(c + 0x18));
            }
        }
    }
}
