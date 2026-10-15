typedef struct { char pad[0xCC]; int flag; char pad2[0x1C]; } BossEnt;
extern int DldSysUndefSymbol;
extern char SH_BossStatusDEFAULT[];
extern int _gameFlagChk(int);

int time_attack_get_clear_num(void)
{
    char *t = (char *)DldSysUndefSymbol == SH_BossStatusDEFAULT ? 0 : SH_BossStatusDEFAULT;
    int n = 0;
    int i;
    int cnt = *(int *)(t + 0xC);
    BossEnt *e = *(BossEnt **)(t + 0x10);
    for (i = 0; i < cnt; i++) {
        int f = e->flag;
        e++;
        if (_gameFlagChk(f))
            n++;
    }
    return n;
}
