typedef union { long l; double d; } DL;
typedef struct Sep {
    int status;
    int unk4;
    int serial;
    int vab;
    int mod;
    int seq;
    int flags;
    int pad1C;
    DL tick;
    DL time;
    DL count;
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
/* Parked: 14 words differ (tested with --asm-fill-delay-slots, which this Sg2 file
   will need once matched). The DFmode count store stays out of the floatdidf branch's
   delay slot like the Original. Left: lui/addiu order before the second loop, the
   &sep->ptr base computed before the dpadd arguments, and the skip test's branch
   shape (the Original takes it with bnel and sb in the likely slot). */
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
        sep->time.l = dpadd(sep->time.l, sep->tick.l);
        while (dpcmp(sep->time.l, sep->count.l) >= 0) {
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
            { DL u; u.l = t; sep->count.d = u.d; }
            sep->time.d = 0;
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
