typedef struct { int name; char pad[0x18]; } Weapon;
typedef struct { char pad[0x10]; Weapon *list; } WeaponList;
extern int DldSysUndefSymbol;
extern WeaponList SH_WeaponListDEFAULT;
int getWeaponName(int i)
{
    WeaponList *l = DldSysUndefSymbol != (int)&SH_WeaponListDEFAULT ? &SH_WeaponListDEFAULT : 0;
    return l->list[i].name;
}
