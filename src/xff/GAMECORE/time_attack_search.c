extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int B_001887B8;
extern int B_001887BC;
extern unsigned int B_001887C0;
extern unsigned int D_0017A92C;
extern float D_0017A928;
extern int gameflowStartMenuKaisou;
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(char *);
extern unsigned int bossStatGetFromIconGObj(int, int *, int *);
extern float getBossIndexTimeAttackBestTime(int);
extern void setBossIndexTimeAttackBestTime(int, float);

void time_attack_search(void *actor)
{
    int icon1 = 0;
    unsigned int boss = 0;
    int icon2 = 0;
    char *chara = GetCharacterClass(actor);
    char *layout = GetLayoutClass(actor);
    void *g1 = GetGeometryPointerObject(chara + 0xEF0);
    void *g2 = GetGeometryPointerObject(layout + 0xC0);
    int *sh;
    float best;

    if (g1 != 0 && *(int *)(chara + 0xF3C) != 0)
        icon1 = *(int *)(GetLayoutClass(g1) + 0x1A4);
    if (g2 != 0 && *(int *)(layout + 0x124) != 0)
        icon2 = *(int *)(GetLayoutClass(g2) + 0x1A4);
    if (icon1 != 0)
        boss = bossStatGetFromIconGObj(icon1, &B_001887B8, &B_001887BC);
    if (boss == 0)
        boss = bossStatGetFromIconGObj(icon2, &B_001887B8, &B_001887BC);
    D_0017A92C = boss;
    sh = DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    B_001887C0 = (boss - sh[4]) / 0xEC;
    best = getBossIndexTimeAttackBestTime(B_001887C0);
    D_0017A928 = best;
    setBossIndexTimeAttackBestTime(B_001887C0, best);
    gameflowStartMenuKaisou = B_001887BC;
}
