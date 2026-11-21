typedef struct {
    int on;
    int a;
    int mod;
    char pad0C[0x20 - 0xC];
    int x20;
    int x24;
    int x28;
    int x2C;
    double tempo;
    double d38;
    double d40;
    double d48;
    double d50;
    double d58;
    unsigned char *p60;
    unsigned char *p64;
    char pad68[0x78 - 0x68];
    double d78;
} Smfp;

extern Smfp B_000E0DC0[];
extern double dpmul(double, double);
extern double dpdiv(double, double);
extern unsigned int Sg2CtrlGetTickMode(void);
extern int Sg2SmfpSetParam(int, int, int, int);

int Sg2SmfpPlay(int i)
{
    Smfp *s;
    double t;
    unsigned long v;

    if (i >= 0) {
        if (i & 0x10000) {
            i &= ~0x10000;
            Sg2SmfpSetParam(B_000E0DC0[i].mod, 0x800, 1, 0);
        }
        s = &B_000E0DC0[i];
        s->tempo = 120.0;
        t = 1000000.0 / (60000000.0 / s->tempo) * s->d38;
        s->d40 = t / Sg2CtrlGetTickMode();
        s->d40 = dpmul(s->d40, s->d78) / 100.0;
        B_000E0DC0[i].x20 = 4;
        B_000E0DC0[i].x24 = 4;
        B_000E0DC0[i].x2C = 1;
        B_000E0DC0[i].x28 = 1;
        B_000E0DC0[i].p60 = B_000E0DC0[i].p64;
        B_000E0DC0[i].d48 = 0;
        B_000E0DC0[i].d58 = 0;
        v = 0;
        do {
            v = (v << 7) + (*s->p60 & 0x7F);
        } while (*s->p60++ & 0x80);
        B_000E0DC0[i].d50 = v;
        B_000E0DC0[i].on = 2;
    }
    return 0;
}
