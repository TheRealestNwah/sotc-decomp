typedef struct {
    char pad0[0x8];
    unsigned int val;
    int a;
    int pad10;
    int b;
    int c;
    char pad1C[0x50 - 0x1C];
} SepEntry;

typedef struct {
    int idx;
    unsigned int val;
} Cand;

extern SepEntry B_000DD700[];
extern void Sg2SepStopSndOff(int);

#ifdef NONMATCHING
/* Parked: 7 words differ (second loop pointer in a1 instead of a0, set before the branch) */
static void func_00025B50(int a, int b, int c, unsigned int limit)
{
    Cand list[48];
    Cand best;
    Cand *p;
    SepEntry *tbl = B_000DD700;
    int *e = &tbl->pad10;
    unsigned int n = 0;
    unsigned int *v;
    int i;

    for (i = 0, p = list; i < 32; i++, e += 0x14) {
        if (e[-1] == a && e[1] == b && e[2] == c) {
            p->idx = i;
            p->val = e[-2];
            p++;
            n++;
        }
    }
    if (limit < n) {
        best.idx = list[0].idx;
        best.val = list[0].val;
        for (i = 1, v = &list[1].val; i < n; i++, v += 2) {
            if (*v < best.val) {
                best.idx = v[-1];
                best.val = v[0];
            }
        }
        Sg2SepStopSndOff(best.idx);
        B_000DD700[best.idx].b = -1;
    }
}
#endif
