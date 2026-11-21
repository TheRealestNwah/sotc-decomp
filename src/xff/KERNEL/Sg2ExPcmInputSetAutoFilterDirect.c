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
/*
 * Parked: 10 words differ. Pinning intr to $s1 gives the original's
 * callee-saved assignment (ch=s2, arg2=s3, arg1=s4, base=s0, intr=s1). The
 * remaining diffs are the filter pointer: the original builds it in $t1 and
 * copies it to $s0 after base is passed in $a0; here it is built in $s0.
 * Pinning the inline's copy to $s0 as well clobbers base (wrong code).
 */
static inline void filterReset(Filter *f)
{
    register Filter *g = f;
    __asm__("" : "+r"(g));
    f->b = -1;
    g->d = 0;
}

void Sg2ExPcmInputSetAutoFilterDirect(unsigned int port, int ch, int arg1, int arg2, float f0, float f1)
{
    PcmChannel *base;
    register int intr __asm__("$17");

    if (port >= 4) {
        return;
    }
    base = B_000E251C[port].ch;
    intr = DIntr();
    {
        int off = ch * sizeof(PcmChannel);
        register int foff __asm__("$8") = off + 0x30;
        register Filter *fp __asm__("$9") = (Filter *)((char *)base + foff);
        ((PcmChannel *)((char *)base + off))->filter.a = 0;
        filterReset(fp);
    }
    func_0002E728(base, ch, arg1, arg2 != -1000 ? arg2 : 0, f0, f1);
    if (intr) {
        EIntr();
    }
}
#endif
