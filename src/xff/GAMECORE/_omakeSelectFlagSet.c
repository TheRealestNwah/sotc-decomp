/* ~55 diffs, 1 word longer (75 vs 74). Selecting an omake flag clears every flag in the same exclusive class (the lists D_0017A038 / D_0017A040 / D_0017A048 from the RO_0017CB00 pointer table, null terminated, template: findCls in _omakeSelectFlagCls.c) and then sets the new bit in B_00184782. Remaining diffs: the Original keeps n in $a2 and the found list in $a3 with the pointer-table cursor in $t0; ours uses $a3 for n and $t1 (goto-style and register-pin variants: 59-64). */
extern unsigned char D_0017A038[];
extern unsigned char D_0017A040[];
extern unsigned char D_0017A048[];
extern unsigned char B_00184782[];

#ifdef NONMATCHING
static inline unsigned char *findCls(int i)
{
    unsigned char *tbl[4] = { D_0017A038, D_0017A040, D_0017A048, 0 };
    unsigned char **p = tbl;
    unsigned char *list;
    int j;

    for (list = *p; list != 0; list = *++p) {
        for (j = 0; list[j] != 0; j++) {
            if (i == list[j])
                return list;
        }
    }
    return 0;
}

static void _omakeSelectFlagSet(int n)
{
    unsigned char *found = findCls(n);
    int j;

    if (found != 0) {
        for (j = 0; found[j] != 0; j++)
            B_00184782[found[j] / 8] &= ~(1 << (found[j] & 7));
    }
    B_00184782[n / 8] |= 1 << (n & 7);
}
#endif
