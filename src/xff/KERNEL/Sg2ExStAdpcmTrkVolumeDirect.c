typedef struct {
    int l, r;
} Sg2Vol;

typedef struct {
    char pad00[0x30];
    int maxL[8];
    int maxR[8];
} Sg2Max;

typedef struct {
    char pad00[0x240];
    Sg2Vol vol[8];
} Sg2VolTab;

typedef struct {
    int state;
    char pad04[0x9C];
    long mask;
} Sg2ExSt;

extern void func_000205D0(Sg2ExSt *, int, int);

/* Parked: 55 words differ (loop register allocation and mask test scheduling) */
#ifdef NONMATCHING
int Sg2ExStAdpcmTrkVolumeDirect(Sg2ExSt *st, int trk, int l, int r)
{
    int i;
    int n;
    Sg2Max *m = (Sg2Max *)((char *)st + 0x10);
    Sg2VolTab *v = (Sg2VolTab *)((char *)st + 0xC);

    v->vol[trk].l = 8191.0f / m->maxL[trk] * l / 127.0f;
    v->vol[trk].r = 8191.0f / m->maxR[trk] * r / 127.0f;
    if (st->state < 0x10)
        return -1;
    n = trk;
    for (i = 0; i < 0x30; i++) {
        if (st->mask & (1L << i)) {
            if (--n < 0) {
                func_000205D0(st, i, trk);
                return 0;
            }
        }
    }
    return -1;
}
#else
extern int Sg2ExStAdpcmTrkVolumeDirect(Sg2ExSt *st, int trk, int l, int r);
#endif
