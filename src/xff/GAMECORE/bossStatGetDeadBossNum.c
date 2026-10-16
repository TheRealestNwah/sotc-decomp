extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int _gameFlagChk(int);

int bossStatGetDeadBossNum(void)
{
    int *sh = DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    char *e = (char *)sh[4];
    int n = 0;
    int i;

    for (i = 0; i < sh[3]; i++) {
        if (!_gameFlagChk(*(int *)(e + 0x18)))
            n++;
        e += 0xEC;
    }
    return n;
}
