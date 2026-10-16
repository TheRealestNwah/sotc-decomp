typedef struct {
    int a;
    int flag;
    char pad[0x14];
} Weapon;

extern int *DldSysUndefSymbol;
extern int SH_WeaponListDEFAULT[];
extern int D_0017B330;
extern int D_0017B334;
extern int _omakeSelectFlagChk(int);
extern void CancelSwordEffect(void);
extern void setWeaponSpriteStatus(int, int);

int selectWeaponNext(int cur)
{
    int *sh = DldSysUndefSymbol != SH_WeaponListDEFAULT ? SH_WeaponListDEFAULT : 0;
    Weapon *tab = (Weapon *)sh[4];
    int i;

    i = cur;
    for (;;) {
        if (++i >= 10)
            i = 1;
        if (i == cur)
            break;
        if (_omakeSelectFlagChk(tab[i].flag))
            break;
    }
    CancelSwordEffect();
    D_0017B334 = D_0017B330;
    D_0017B330 = i;
    setWeaponSpriteStatus(i, D_0017B334);
    return i;
}
