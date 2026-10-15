typedef struct { int name; int flag; char pad[0x14]; } Weapon;
typedef struct { char pad[0x10]; Weapon *list; } WeaponList;
extern int DldSysUndefSymbol;
extern WeaponList SH_WeaponListDEFAULT;
extern int _omakeSelectFlagChk(int);

int chkPossessWeapon(int i)
{
    WeaponList *l = DldSysUndefSymbol != (int)&SH_WeaponListDEFAULT ? &SH_WeaponListDEFAULT : 0;
    return _omakeSelectFlagChk(l->list[i].flag);
}
