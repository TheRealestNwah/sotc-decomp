typedef struct { int status, previous, unk8, vab, mod, x14, x18; char pad1C[52]; } Sep;
extern Sep B_000DD700[];
extern int B_000DE100;
extern void *memset(void *, int, unsigned int);
extern int Sg2CtrlEntryTickProcById(int, void (*)(void));
extern void Sg2SepTickProc(void);

#ifdef NONMATCHING
/* Parked: 35 words differ (memset address kept as offset+base, stores through a +0x10 biased pointer) */
int Sg2SepInit(void)
{
    int i;

    for (i = 0; i < 32; i++) {
        Sep *sep;
        memset((char *)B_000DD700 + i * sizeof(Sep), 0, sizeof(Sep));
        sep = &B_000DD700[i];
        sep->status = 0;
        sep->x14 = -1;
        sep->x18 = -1;
        sep->vab = -1;
    }
    B_000DE100 = 1;
    Sg2CtrlEntryTickProcById(1, Sg2SepTickProc);
    return 0;
}
#endif
