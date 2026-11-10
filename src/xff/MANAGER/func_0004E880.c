/* ~136 diffs, same length (184 words). Applies a character-class "additional motion" table: chara+0x750 points at a dld list (count at the base +0xC, 16-byte entries); each entry resolves a run of 0x30-byte condition records (func_0004C898 must accept every record up to the one whose first word is 1), optionally gated by a bit of cls2+0x1C0|0x1C8 chosen by the entry at e+4 (kind 1 forces true, kind 2 forces false), and when the result is positive requests RequestCharacterClassAdditionMotionChange(chara, resolved e+8). The Original materialises the count in $a2 first (the undef-symbol test is a branch-likely) and copies it to $s4 afterwards, and keeps the e+4 handle in $a1; ours loads the module base into $a1 and the count straight into $s4 (a returning dldCount helper made it worse: 164). */
extern int DldSysUndefSymbol;
extern int func_0004C898(void *, void *, void *, void *);
extern void RequestCharacterClassAdditionMotionChange(void *, void *);

static inline char *dldBase(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? t : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

#ifdef NONMATCHING
static void func_0004E880(void *a0, char *chara, char *cls2, int flag)
{
    char *tbl = *(char **)(chara + 0x750);
    unsigned int *h;
    char *base;
    int cnt;
    int n;
    char *e;
    unsigned long mask;
    int ok;

    if (tbl == 0)
        return;
    h = (unsigned int *)(tbl + 4);
    base = dldBase(h);
    cnt = base != 0 ? *(int *)(base + 0xC) : 0;
    n = cnt;
    e = dldResolve(h);
    mask = *(unsigned long *)(cls2 + 0x1C0) | *(unsigned long *)(cls2 + 0x1C8);
    if (n <= 0)
        return;
    do {
        char *sub = dldResolve((unsigned int *)e);

        if (*(int *)sub == 1) {
            ok = 1;
        } else {
            char *a3 = sub;

            do {
                sub += 0x30;
                if (func_0004C898(a0, chara, cls2, a3) == 0) {
                    ok = 0;
                    goto next;
                }
                a3 = sub;
            } while (*(int *)sub != 1);
            ok = 1;
        }
    next:
        if (flag != 0) {
            char *p = dldResolve((unsigned int *)(e + 4));

            if (p != 0) {
                unsigned long m = mask & (1UL << *(int *)(p + 4));
                int k = *(int *)(p + 8);

                if (k == 1) {
                    if (m != 0)
                        ok = 1;
                } else if (k == 2) {
                    if (m != 0)
                        ok = 0;
                }
            }
        }
        if (ok > 0)
            RequestCharacterClassAdditionMotionChange(chara, dldResolve((unsigned int *)(e + 8)));
        n--;
        e += 0x10;
    } while (n != 0);
}
#endif
