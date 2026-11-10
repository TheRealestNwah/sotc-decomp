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

/*
 * The inline's parameter copy is pinned to $a0 and the filter pointer to $a1,
 * reproducing the original's `daddu $a0, $a1` copy.
 */
static inline void filterReset(Filter *f)
{
    register Filter *g __asm__("$4") = f;
    __asm__("" : "+r"(g));
    f->b = -1;
    g->d = 0;
}

#ifdef NONMATCHING
/*
 * Parked: 1 word differs. The original computes the filter pointer as
 * `addu $a1, $s1, $a0` (base first); this emits `addu $a1, $a0, $s1`.
 */
void Sg2ExPcmOutputSetAutoFilterDirect(int ch, int arg1, int arg2, float f0, float f1)
{
    PcmOutput *base = B_000E2368;
    int intr = DIntr();

    {
        int off = ch * sizeof(PcmOutput);
        register int foff __asm__("$4") = off + 0x30;
        register Filter *fp __asm__("$5") = (Filter *)((char *)base + foff);
        ((PcmOutput *)((char *)base + off))->filter.a = 0;
        filterReset(fp);
    }
    if (intr) {
        EIntr();
    }
    func_0002E728(base, ch, arg1, arg2 != -1000 ? arg2 : 0, f0, f1);
}
#endif
