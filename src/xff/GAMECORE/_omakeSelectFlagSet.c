/* 12 diffs, same length (74 words). Selecting an omake flag clears every flag in the same exclusive class (the lists D_0017A038 / D_0017A040 / D_0017A048 from the RO_0017CB00 pointer table, null terminated, template: findCls in _omakeSelectFlagCls.c) and then sets the new bit in B_00184782. The final set goes through B_00184778 + 0xA so gcc does not share the B_00184782 address with the loop. Remaining diffs: gcc hoists the B_00184782 address out of the clear loop (lui/addiu before the loop, $t2), where the Original rebuilds it every iteration as an indexed la ($at). */
extern unsigned char D_0017A038[];
extern unsigned char D_0017A040[];
extern unsigned char D_0017A048[];
extern unsigned char B_00184782[];
extern unsigned char B_00184778[];

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

void _omakeSelectFlagSet(int n)
{
    unsigned char *found = findCls(n);
    int j;

    if (found != 0) {
        for (j = 0; found[j] != 0; j++)
            B_00184782[found[j] / 8] &= ~(1 << (found[j] & 7));
    }
    B_00184778[0xA + n / 8] |= 1 << (n & 7);
}
#endif
