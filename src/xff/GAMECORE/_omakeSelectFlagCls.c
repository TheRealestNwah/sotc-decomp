extern unsigned char D_0017A048[];
extern unsigned char B_00184782[];
typedef struct {
    char pad0[0xB];
    unsigned char flags;
    char padC[0x14];
    int x20;
} OmakeStat;

extern OmakeStat B_00184778;

void _omakeSelectFlagCls(int n)
{
    unsigned char *tbl[2] = { D_0017A048, 0 };
    unsigned char **p = tbl;
    unsigned char *found;
    unsigned char *s;

    for (; (s = *p) != 0; p++) {
        int j;

        for (j = 0; s[j] != 0; j++) {
            if (n == s[j]) {
                found = s;
                goto done;
            }
        }
    }
    found = 0;
done:
    B_00184782[n / 8] &= ~(1 << (n & 7));
    if (found != 0) {
        OmakeStat *st = &B_00184778;

        if (st->x20 != 0) {
            unsigned char *f = &st->flags;

            *f |= 4;
        }
    }
}
