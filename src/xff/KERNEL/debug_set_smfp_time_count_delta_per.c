typedef struct {
    int on;
    int a;
    int mod;
    char pad0C[0x30 - 0xC];
    double tempo;
    double d38;
    double d40;
    char pad48[0x78 - 0x48];
    double d78;
} Smfp;

/* Called by name: as an operator, gcc drops the intermediate d40 store below as dead. */
extern double dpmul(double, double);
extern Smfp B_000E0DC0[];
extern unsigned int Sg2CtrlGetTickMode(void);

void debug_set_smfp_time_count_delta_per(int i, int delta)
{
    Smfp *s = &B_000E0DC0[i];
    if (s->mod >= 0) {
        double t, tp;
        s->d78 = delta;
        tp = s->tempo;
        s->tempo = tp;
        t = 1000000.0 / (60000000.0 / tp) * s->d38;
        s->d40 = t / Sg2CtrlGetTickMode();
        s->d40 = dpmul(s->d40, s->d78) / 100.0;
    }
}
