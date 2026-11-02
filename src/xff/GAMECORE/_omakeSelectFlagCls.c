/* omakeGetAndSelectCls and _omakeSelectFlagCls share one class table
   initializer (RO_0017CB10): gcc emits identical constants once per file. */
extern unsigned char D_0017A048[];
extern unsigned char B_0018477A[];
extern unsigned char B_00184782[];
typedef struct {
    char pad0[0xB];
    unsigned char flags;
    char padC[0x14];
    int x20;
} OmakeStat;

extern OmakeStat B_00184778;

static inline unsigned char *findCls(int i)
{
    unsigned char *tbl[2] = { D_0017A048, 0 };
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

void omakeGetAndSelectCls(int i)
{
    unsigned char *found;

    B_0018477A[i / 8] &= ~(1 << (i & 7));
    found = findCls(i);
    B_00184782[i / 8] &= ~(1 << (i & 7));
    /* Byte poke rather than a struct field; a field folds the 0xB into the lbu offset. */
    if (found != 0 && B_00184778.x20 != 0)
        ((unsigned char *)&B_00184778)[0xB] |= 4;
}

void _omakeSelectFlagCls(int n)
{
    unsigned char *found = findCls(n);

    B_00184782[n / 8] &= ~(1 << (n & 7));
    if (found != 0) {
        OmakeStat *st = &B_00184778;

        if (st->x20 != 0) {
            unsigned char *f = &st->flags;

            *f |= 4;
        }
    }
}
