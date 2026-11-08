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
} PcmChannel;

typedef struct {
    PcmChannel ch[2];
    char pad188[0x1D4 - 0x188];
} PcmInput;

extern int DIntr(void);
extern int EIntr(void);
extern PcmInput B_000E251C[];
extern void func_0002E728(PcmChannel *in, int ch, int arg1, int arg2, float f0, float f1);

#ifdef NONMATCHING
/* Parked: 29 words differ (filter pointer kept in s0, two extra moves) */
static inline void filterReset(Filter *f)
{
    f->b = -1;
    f->d = 0;
}

void Sg2ExPcmInputSetAutoFilterDirect(unsigned int port, int ch, int arg1, int arg2, float f0, float f1)
{
    PcmChannel *base;
    int intr;

    if (port >= 4) {
        return;
    }
    base = B_000E251C[port].ch;
    intr = DIntr();
    base[ch].filter.a = 0;
    filterReset(&base[ch].filter);
    func_0002E728(base, ch, arg1, arg2 != -1000 ? arg2 : 0, f0, f1);
    if (intr) {
        EIntr();
    }
}
#endif
