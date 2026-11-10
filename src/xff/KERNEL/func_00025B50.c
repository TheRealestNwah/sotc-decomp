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
        i = 1;
        if (i < n) {
            v = &list[1].val;
            do {
                if (*v < best.val) {
                    best.idx = v[-1];
                    best.val = v[0];
                }
                i++; v += 2;
            } while (i < n);
        }
        Sg2SepStopSndOff(best.idx);
        B_000DD700[best.idx].b = -1;
    }
}
