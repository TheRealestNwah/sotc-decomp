typedef struct {
    int a;
    int b;
    int c;
    int d;
} Filter;

typedef struct {
    char pad0[0x30];
    Filter filter;
    char pad40[0xC4 - 0x40];
} PcmOutput;

extern int DIntr(void);
extern int EIntr(void);
extern PcmOutput B_000E2368[];
extern void func_0002E728(PcmOutput *out, int ch, int arg1, int arg2, float f0, float f1);

static inline void filterReset(Filter *f)
{
    f->b = -1;
    f->d = 0;
}

#ifdef NONMATCHING
/* Parked: 31 words differ (register allocation and ordering) */
void Sg2ExPcmOutputSetAutoFilterDirect(int ch, int arg1, int arg2, float f0, float f1)
{
    PcmOutput *base = B_000E2368;
    int intr = DIntr();

    base[ch].filter.a = 0;
    filterReset(&base[ch].filter);
    if (intr) {
        EIntr();
    }
    func_0002E728(base, ch, arg1, arg2 != -1000 ? arg2 : 0, f0, f1);
}
#endif
