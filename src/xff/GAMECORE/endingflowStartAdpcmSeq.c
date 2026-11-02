typedef struct AdpcmInfo {
    int unk0;
    int unk4;
    int id;
} AdpcmInfo;

typedef struct AdpcmSeq {
    int active;
    int unk4;
    int unk8;
    int handle;
    AdpcmInfo info;
} AdpcmSeq;

extern AdpcmSeq B_00183E10[3];
extern int B_00183E64;
extern AdpcmInfo *D_0017A010;
extern void func_00013AF0();

extern int bgmStandby(int, int, void (*)(), void *);
extern void scrRun(void);

static inline AdpcmSeq *start_adpcm_seq(AdpcmInfo *info) {
    int i;
    AdpcmSeq *seq;

    for (i = 0; i < 3; i++) {
        if (B_00183E10[i].handle == 0)
            goto found;
    }
    return 0;
found:
    seq = &B_00183E10[i];
    seq->info = *info;
    seq->handle = bgmStandby(seq->info.id, 0, func_00013AF0, seq);
    if (seq->handle)
        seq->active = 1;
    return seq;
}

void endingflowStartAdpcmSeq(AdpcmInfo *info) {
    D_0017A010 = info;
    B_00183E64 = -1;
    while (!start_adpcm_seq(D_0017A010))
        scrRun();
}
