typedef struct {
    char pad0[0x18];
    int flag;
    char pad1[0x8];
    unsigned int layout;
    char pad2[0x8C];
    float hp;
    float grip;
    char pad3[0x30];
} BossStatus;

extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int B_00183E0C;
extern BossStatus *D_00179F98;
extern BossStatus *B_00183DA8;
extern void _gameFlagCls(int);
extern void _gameFlagSet(int);
extern int _gameFlagChk(int);
extern void bossStatSetActiveBoss(BossStatus *);
extern void addPlayerMaxHp(float);
extern void addPlayerMaxGrip(float);

static inline char *dldResolve(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline int *bossTable(void)
{
    return DldSysUndefSymbol == SH_BossStatusDEFAULT ? 0 : SH_BossStatusDEFAULT;
}

static void func_000101D0(void)
{
    int *sh = bossTable();
    BossStatus *base = (BossStatus *)sh[4];
    int n = sh[3];
    BossStatus *p;
    int i;

    for (i = 0; i < B_00183E0C; i++) {
        D_00179F98 = &base[i];
        _gameFlagCls(base[i].flag);
    }
    for (; i < n; i++)
        _gameFlagSet(base[i].flag);
    {
    int *sh2 = bossTable();
    int j;
    p = (BossStatus *)sh2[4];
    for (j = 0; j < sh2[3]; j++, p++) {
        int f = *(int *)(dldResolve(&p->layout) + 0xC);

        if (p == 0)
            _gameFlagCls(f);
        else
            _gameFlagSet(f);
    }
    }
    base += B_00183E0C;
    B_00183DA8 = base;
    bossStatSetActiveBoss(base);
}

/* Matches, but spimdisasm merged it into func_000101D0's asm with no label at
 * 0x103A8, so the splice step can't place it yet. */
#ifdef NONMATCHING
static void func_000103A8(void)
{
    int *sh = DldSysUndefSymbol == SH_BossStatusDEFAULT ? 0 : SH_BossStatusDEFAULT;
    int n = sh[3];
    BossStatus *base = (BossStatus *)sh[4];
    BossStatus *p;
    int i;

    for (i = 0; i < n; i++) {
        p = &base[i];
        if (!_gameFlagChk(p->flag)) {
            addPlayerMaxHp(-p->hp);
            addPlayerMaxGrip(-p->grip);
        }
    }
    for (i = 0; i < B_00183E0C; i++) {
        addPlayerMaxHp(base[i].hp);
        addPlayerMaxGrip(base[i].grip);
    }
}
#endif
