/* ~70 diffs, 1 word short (79 vs 80). Weapon-slot cycling (SH_WeaponListDEFAULT table of 0x1C-byte entries, flag word at +4): with force set it cancels the sword effect, makes `w` the current weapon (D_0017B330) and remembers the previous one (D_0017B334), calling setWeaponSpriteStatus(w, prev); without force and when w is already current it walks to the next owned weapon (wrapping 10 -> 1 via the movz in the Original), falling back to -1 (none) when it comes back to w. Returns D_0017B330. Remaining diffs: the Original keeps -1 and the second sprite call in different registers, wraps at the loop top with a single saved register set (s0-s5, no $s6) and reaches D_0017B330 through a shared $s4 base while ours keeps pointer registers; ours spills an extra $s6. */
extern char SH_WeaponListDEFAULT[];
extern char *DldSysUndefSymbol;
extern int D_0017B330;
extern int D_0017B334;
extern void CancelSwordEffect(void);
extern void setWeaponSpriteStatus(int, int);
extern int _omakeSelectFlagChk(int);

#ifdef NONMATCHING
int setIsWeapon(int w, int force)
{
    char *l = SH_WeaponListDEFAULT != DldSysUndefSymbol ? SH_WeaponListDEFAULT : 0;
    char *tbl = *(char **)(l + 0x10);
    int i;
    int prev;

    if (force != 0) {
        CancelSwordEffect();
        prev = D_0017B330;
        D_0017B330 = w;
        D_0017B334 = prev;
        setWeaponSpriteStatus(w, prev);
        return D_0017B330;
    }
    if (D_0017B330 == w) {
        i = w + 1;
        for (;;) {
            if (!(i < 10))
                i = 1;
            if (i == w) {
                D_0017B330 = -1;
                setWeaponSpriteStatus(-1, D_0017B334);
                break;
            }
            if (_omakeSelectFlagChk(*(int *)(tbl + i * 0x1C + 4)) != 0) {
                CancelSwordEffect();
                prev = D_0017B330;
                D_0017B330 = i;
                D_0017B334 = prev;
                setWeaponSpriteStatus(i, prev);
                break;
            }
            i++;
        }
    }
    return D_0017B330;
}
#endif
