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
static void func_0002F0D8(unsigned int port)
{
    PcmIn *p;
    int v, l, pan;
    unsigned short t;

    if (port < 4) {
        p = &B_000E2518[port];
        v = p->vol;
        l = v * p->volL;
        pan = p->pan;
        v = v * p->volR;
        t = pan_tbl[pan];
        p->outL = l * (t >> 8) / 127;
        p->outR = v * (t & 0xFF) / 127;
    }
}
