extern int *DldSysUndefSymbol;
extern int SH_GameObjectStatusDEFAULT[];
extern int SH_TimeAttackItemListDEFAULT[];

typedef struct {
    unsigned int h;
    char pad4[0x10];
} GObjStatus;

static inline int *dldTable(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? t : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void time_attack_init_gstat_adrs(void)
{
    int *sh = DldSysUndefSymbol == SH_GameObjectStatusDEFAULT ? 0 : SH_GameObjectStatusDEFAULT;
    GObjStatus *e = (GObjStatus *)sh[4];
    int i;

    for (i = 0; i < sh[3]; i++, e++) {
        if (dldTable(&e->h) == (DldSysUndefSymbol != SH_TimeAttackItemListDEFAULT ? SH_TimeAttackItemListDEFAULT : 0))
            *(int *)(dldResolve(&e->h) + 0x10) = (int)e;
    }
}
