extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int D_00179F90;
extern char *D_00179F94;
extern int _gameWorkChk(int);

char *bossStatGetActiveBoss(void)
{
    int n = _gameWorkChk(8);
    int *sh;

    if (n == D_00179F90)
        return D_00179F94;
    D_00179F90 = n;
    if (n == -1) {
        D_00179F94 = 0;
        return 0;
    }
    sh = DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    D_00179F94 = (char *)sh[4] + n * 0xEC;
    return D_00179F94;
}
