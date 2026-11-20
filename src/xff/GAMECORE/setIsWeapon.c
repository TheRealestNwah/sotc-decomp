/* 7 diffs, same size (80 words). Weapon-slot cycling (SH_WeaponListDEFAULT table of 0x1C-byte entries, flag word at +4): with force set it cancels the sword effect, makes `w` the current weapon (D_0017B330) and remembers the previous one (D_0017B334), calling setWeaponSpriteStatus(w, prev); without force and when w is already current it walks to the next owned weapon (wrapping 10 -> 1), falling back to -1 (none) when it comes back to w. Returns D_0017B330. The swap sequence is inlined twice, as in the Original. Writing the swap as a chained assignment (`D_0017B334 = prev = D_0017B330`) fixes the $s4/$s5 base choice and the second swap's scheduling. Remaining diffs: only $v0/$v1 swapped in the prologue's list-pointer select (SH_WeaponListDEFAULT vs DldSysUndefSymbol); compare order, ternary/if forms, int typing and extern order all leave it. */
extern char SH_WeaponListDEFAULT[];
extern char *DldSysUndefSymbol;
extern int D_0017B330;
extern int D_0017B334;
extern void CancelSwordEffect(void);
extern void setWeaponSpriteStatus(int, int);
extern int _omakeSelectFlagChk(int);

#ifdef NONMATCHING
static inline void changeWeapon(int x)
{
    int prev;

    CancelSwordEffect();
    D_0017B334 = prev = D_0017B330;
    D_0017B330 = x;
    setWeaponSpriteStatus(x, prev);
}

int setIsWeapon(int w, int force)
{
    int i;
    char *l = SH_WeaponListDEFAULT;
    char *tbl;
    if (l == DldSysUndefSymbol)
        l = 0;
    tbl = *(char **)(l + 0x10);

    if (force != 0) {
        changeWeapon(w);
    } else if (w == D_0017B330) {
        i = w;
        while (1) {
            i++;
            if (i >= 10)
                i = 1;
            if (i == w)
                break;
            if (_omakeSelectFlagChk(*(int *)(tbl + i * 0x1C + 4)) != 0)
                break;
        }
        if (i == w) {
            D_0017B330 = -1;
            setWeaponSpriteStatus(-1, D_0017B334);
        } else {
            changeWeapon(i);
        }
    }
    return D_0017B330;
}
#endif
