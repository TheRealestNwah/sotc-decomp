typedef struct {
    char pad0[0x1AC];
    int vol;
    int volL;
    int volR;
    int outL;
    int outR;
    int pan;
    char pad1C4[0x1D4 - 0x1C4];
} PcmIn;

extern PcmIn B_000E2518[];
extern unsigned short pan_tbl[];

#ifdef NONMATCHING
/* Parked: 5 words differ, only in R5900 pipe choice (Original puts vol*volR on mult and the outL divide on div, outR on div1; gcc swaps both pairs) */
static void func_0002F0D8(unsigned int port)
{
    PcmIn *p;
    register int l __asm__("$3");
    register int v __asm__("$4");
    register int c __asm__("$8");
    unsigned short t;

    if (port < 4) {
        p = &B_000E2518[port];
        v = p->vol;
        l = v * p->volL;
        c = p->volR;
        v = v * c;
        t = pan_tbl[p->pan];
        p->outL = l * (t >> 8) / 127;
        p->outR = v * (t & 0xFF) / 127;
    }
}
#endif
