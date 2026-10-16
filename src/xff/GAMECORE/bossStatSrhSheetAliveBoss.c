extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int _gameFlagChk(int);

char *bossStatSrhSheetAliveBoss(void)
{
    int *sh = DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    char *e = (char *)sh[4];
    int i;

    for (i = 0; i < sh[3]; i++) {
        if (_gameFlagChk(*(int *)(e + 0x18)))
            return e;
        e += 0xEC;
    }
    return 0;
}
