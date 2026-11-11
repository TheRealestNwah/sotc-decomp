extern char B_001A57E8[];

#ifdef NONMATCHING /* 114 diffs: three table lookups (stride 0x24 items, count at +0x90 of a 0x98-byte entry); loop shapes and shared-return layout differ, the first loop has no precheck in the original */
static inline char *findSlot(char *tab, int key)
{
    char *e = tab;
    char *p = tab;
    int n = *(int *)(tab + 0x90);
    int i;

    for (i = 0; i < n; i++) {
        if (key == *(int *)(*(char **)p + 0x1C))
            return e;
        p += 0x24;
        e += 0x24;
    }
    return 0;
}

int func_000F6228(char *a)
{
    unsigned n = *(unsigned *)(a + 0x380);
    int i;
    char *s = a;
    int key;
    char *slot;

    if (n != 0) {
        for (i = 0; (unsigned)i < n; i++, s += 0x20) {
            slot = 0;
            if (i < 0x14) {
                slot = 0;
                if ((unsigned)i < n)
                    slot = s + 0x100;
            }
            key = *(int *)(slot + 0x1C);
            if (key >= 0) {
                if (findSlot(B_001A57E8 + *(int *)(a + 0x3C50) * 0x98, key) == 0)
                    return 0;
            }
        }
    }
    key = *(int *)(a + 0x420);
    if (key >= 0) {
        if (findSlot(B_001A57E8 + *(int *)(a + 0x3C50) * 0x98, key) == 0)
            return 0;
    }
    key = *(int *)(a + 0x84);
    if (key >= 0) {
        if (findSlot(B_001A57E8 + *(int *)(a + 0x3C50) * 0x98, key) == 0)
            return 0;
    }
    return 1;
}
#else
extern int func_000F6228(char *);
#endif
