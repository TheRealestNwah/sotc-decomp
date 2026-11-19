/* Finds the boss status entry whose icon (either of two dld references at +0x28 / +0x2C) is icon, or failing that the first boss of the player's current stage area (byArea set). idx receives the entry index, -1 when none. */
extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);
extern int GetStageAreaNumberByPos(int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

char *bossStatGetFromIconGObj(char *icon, int *idx, int *byArea)
{
    int *sh = DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    char *e = (char *)sh[4];
    int area = GetStageAreaNumberByPos(*(int *)(GetLayoutClass(SCRGetFirstObj(gcGlobalVar + 0x2B0)) + 0x134));

    int n = sh[3];

    *byArea = 0;
    for (*idx = 0; *idx < n; (*idx)++, e += 0xEC) {
        if (icon != 0) {
            if (dldResolve((unsigned int *)(e + 0x28)) == icon || dldResolve((unsigned int *)(e + 0x2C)) == icon)
                return e;
        }
        if (area == *(unsigned char *)(e + 0x51)) {
            *byArea = 1;
            return e;
        }
    }
    *idx = -1;
    return 0;
}
