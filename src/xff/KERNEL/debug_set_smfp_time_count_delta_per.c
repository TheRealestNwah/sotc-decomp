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

extern Smfp B_000E0DC0[];
extern unsigned int Sg2CtrlGetTickMode(void);

#ifdef NONMATCHING
/* Parked: 39 words differ (gcc leaves the soft-float libcall delay slots empty; the original fills them) */
void debug_set_smfp_time_count_delta_per(int i, long delta)
{
    Smfp *s = &B_000E0DC0[i];
    if (s->mod >= 0) {
        double t;
        s->d78 = delta;
        t = 1000000.0 / (60000000.0 / s->tempo) * s->d38;
        s->d40 = t / Sg2CtrlGetTickMode();
        s->d40 = s->d40 * s->d78 / 100.0;
    }
}
#endif
