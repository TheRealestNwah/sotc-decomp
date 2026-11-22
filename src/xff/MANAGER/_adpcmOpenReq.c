/* Parked: 5 diffs, same size. Remaining: the scheduler orders the six stores
 * after Sg2ExStAdpcmOpen's argument setup (0x288-0x2A0) as cb/user/f40/file/
 * f278/f27C in the Original, but user/f27C/f278/cb/file here; source order of
 * those statements has no effect. */
#ifdef NONMATCHING
typedef struct {
    char b[56];
} AdpcmSeq;

typedef struct {
    unsigned long lo : 32;
    unsigned long loop : 1;
    unsigned long b33 : 1;
    unsigned long b34 : 1;
    unsigned long b35 : 1;
    unsigned long b36 : 1;
    unsigned long b37 : 1;
    unsigned long b38 : 1;
    unsigned long b39 : 1;
    unsigned long b40 : 1;
    unsigned long slot : 5;
    unsigned long rest : 18;
} AdpcmBits;

typedef struct {
    int active;
    char seq[0x34];
    AdpcmBits bits;
    int f40;
    char pad44[4];
    int f48;
    float f4C;
    float f50;
    float f54;
    float f58;
    float f5C;
    float f60;
    float f64;
    float f68;
    float f6C;
    int f70;
    char pad74[4];
    int f78;
    void (*cb)(void);
    int user;
    char pad84[0x274 - 0x84];
    char *file;
    int f278;
    int f27C;
    char work[0x560 - 0x280];
} AdpcmEntry;

extern void *memcpy(void *, const void *, unsigned int);
extern int DldSysUndefSymbol;
extern char SH_AdpcmFileDEFAULT[];
extern AdpcmEntry B_0014E898[];
extern int D_00139BE4;
extern void Sg2ExStAdpcmWorkClear(void *, int);
extern int soundGetTickProcCnt(void);
extern int Sg2ExStAdpcmOpen(void *, int, int, int, int, int);
extern void iosJumpRecoverPoint(char *, int);
extern void Sg2ExStAdpcmSetLsn(void *, int);
extern void Sg2ExStAdpcmSetUserParam(void *, void *);
extern void Sg2ExStAdpcmPreLoad(void *);

int _adpcmOpenReq(AdpcmSeq *seq, int loop, void (*cb)(void), int user)
{
    register void (*c)(void) __asm__("$22") = cb;
    char *m = DldSysUndefSymbol == (int)SH_AdpcmFileDEFAULT ? 0 : SH_AdpcmFileDEFAULT;
    char *file = *(char **)(m + 0x10);
    AdpcmEntry *e;
    int i;
    int r;

    file += ((int *)seq)[2] * 20;
    for (i = 0; i < 3; i++) {
        e = &B_0014E898[i];
        if (e->active == 0)
            goto found;
    }
    return -1;
found:
    memcpy(e->seq, seq, sizeof(AdpcmSeq));
    e->bits.slot = 0;
    Sg2ExStAdpcmWorkClear(e->work, 0x3B);
    e->bits.loop = loop & 1;
    e->bits.b33 = 0;
    e->bits.b35 = 1;
    e->bits.b34 = 0;
    e->bits.b36 = 0;
    e->bits.b37 = 0;
    e->bits.b38 = 0;
    e->bits.b39 = 0;
    e->f4C = 100.0f;
    e->f50 = 0.0f;
    e->f54 = -1.0f;
    e->f58 = 100.0f;
    e->f64 = 100.0f;
    e->f60 = 100.0f;
    e->f5C = 100.0f;
    e->f68 = e->f50;
    e->f6C = e->f50;
    e->f48 = soundGetTickProcCnt();
    e->bits.b40 = 0;
    e->active = 1;
    {
        int f78 = e->f78;

        e->cb = c;
        e->user = user;
        e->f40 = 0;
        e->file = file;
        e->f278 = 0;
        e->f27C = e->f70;
        r = Sg2ExStAdpcmOpen(e->work, *(int *)(file + 0x10), e->f70, D_00139BE4, f78, 0x4000);
    }
    if (r != 0)
        iosJumpRecoverPoint("_adpcmOpenReq:Sg2ExStAdpcmOpen error %d\n", r);
    Sg2ExStAdpcmSetLsn(e->work, 0);
    Sg2ExStAdpcmSetUserParam(e->work, e);
    Sg2ExStAdpcmPreLoad(e->work);
    return i;
}
#else
extern int _adpcmOpenReq(void *, int, void (*)(void), int);
#endif
