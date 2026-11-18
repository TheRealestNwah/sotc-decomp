typedef struct {
    int on;
    int a;
    int mod;
    char pad0C[0x30 - 0xC];
    long tempo;
    long d38;
    long d40;
    char pad48[0x78 - 0x48];
    long d78;
} Smfp;

extern Smfp B_000E0DC0[];
extern unsigned int Sg2CtrlGetTickMode(void);
/* The soft-double libcalls are called with 64-bit integer types: gcc 2.96 never puts a
   DFmode argument move in a call delay slot, and the Original fills them. dpdiv takes a
   double first argument where it divides a constant, so the constant comes from .rodata. */
typedef long (*DivK)(double, long);
extern long litodp(long);
extern long dpdiv(long, long);
extern long dpmul(long, long);
extern long dpadd(long, long);

#ifdef NONMATCHING
/* Parked: 24 words differ (the unsigned tick-mode fixup: gcc puts the dpadd argument move in
   the bgez delay slot, the Original in the dpadd delay slot). */
void debug_set_smfp_time_count_delta_per(int i, long delta)
{
    Smfp *s = &B_000E0DC0[i];
    if (s->mod >= 0) {
        long t, d, tp;
        int m;

        s->d78 = litodp(delta);
        tp = s->tempo;
        s->tempo = tp;
        t = ((DivK)dpdiv)(60000000.0, tp);
        t = dpmul(((DivK)dpdiv)(1000000.0, t), s->d38);
        m = Sg2CtrlGetTickMode();
        d = litodp(m);
        if (m < 0)
            d = dpadd(d, 0x41F0000000000000 /* 2^32 */);
        s->d40 = dpdiv(t, d);
        s->d40 = dpdiv(dpmul(s->d40, s->d78), 0x4059000000000000 /* 100.0 */);
    }
}
#endif
