typedef struct Sep {
    int status;
    int unk4;
    int serial;
    int vab;
    int mod;
    int seq;
    int flags;
    int pad1C;
    double tick;
    double time;
    double count;
    int unk38;
    int data;
    unsigned char *ptr;
    unsigned char skip;
    char pad45[3];
    unsigned int cmd;
    char pad4C[4];
} Sep;

extern Sep B_000DD700[];
extern int B_000DE320;
extern unsigned char B_000DE220[];
extern int B_000DE210;
extern int B_000DE214;
extern unsigned char B_000DE110[];
extern void (*D_00041430[])(Sep *);
/* The soft-double libcalls are called with 64-bit integer types: gcc 2.96 never puts a
   DFmode argument move in a call delay slot, and the Original fills them. */
extern long __floatdidf(long);
extern long dpadd(long, long);
extern int dpcmp(long, long);
extern int DIntr(void);
extern int EIntr(void);
extern int Sg2ModCheckSndOn(int);
extern void Sg2ModMidiout(int, int, unsigned char *);

#ifdef NONMATCHING
/* Parked: 16 words differ (lui/addiu order before the second loop, dpadd result store
   placement, the skip branch shape and the floatdidf join branch delay slot). */
void Sg2SepTickProc(void)
{
    int enabled;
    Sep *sep;
    int *mod;
    int i;
    int j;
    unsigned long v;
    long t;

    enabled = DIntr();
    sep = B_000DD700;
    for (i = 31; i >= 0; i--, sep++) {
        if (sep->status == 2) {
            if (Sg2ModCheckSndOn(sep->mod) == 0)
                sep->status = 0;
        }
    }
    B_000DE320 = 0;
    sep = B_000DD700;
    mod = &sep->mod;
    for (i = 31; i >= 0; i--, mod += 0x14, sep++) {
        if (sep->status != 1)
            continue;
        B_000DE214 = 0;
        B_000DE210 = 0;
        *(long *)&sep->time = dpadd(*(long *)&sep->time, *(long *)&sep->tick);
        while (dpcmp(*(long *)&sep->time, *(long *)&sep->count) >= 0) {
            if ((signed char)*sep->ptr < 0)
                sep->cmd = *sep->ptr++;
            D_00041430[sep->cmd >> 4](sep);
            if (sep->status == 2)
                break;
            if (sep->skip) {
                sep->skip = 0;
                continue;
            }
            v = 0;
            do {
                v = (v << 7) + (*sep->ptr & 0x7F);
            } while (*sep->ptr++ & 0x80);
            if ((long)v >= 0) {
                t = __floatdidf(v);
            } else {
                t = __floatdidf((v & 1) | (v >> 1));
                t = dpadd(t, t);
            }
            *(long *)&sep->count = t;
            sep->time = 0;
        }
        if (B_000DE210 != 0)
            Sg2ModMidiout(*mod, B_000DE210, B_000DE110);
    }
    if (B_000DE320 != 0) {
        for (j = 0; j < B_000DE320; j += B_000DE220[j + 1] + 2)
            Sg2ModMidiout(B_000DE220[j], B_000DE220[j + 1], &B_000DE220[j + 2]);
        B_000DE320 = 0;
    }
    if (enabled)
        EIntr();
}
#endif
