typedef struct {
    int status;
    int a;
    int mod;
    char pad0C[0x24 - 0xC];
    int x24;
    int x28;
    int x2C;
    char pad30[8];
    double d38;
    double d40;
    double d48;
    double d50;
    double d58;
    unsigned char *p60;
    unsigned char *p64;
    unsigned char cmd;
    char pad69[0x78 - 0x69];
    double d78;
} Smfp;

extern Smfp B_000E0DC0[];
extern unsigned char B_000E11C0;
extern unsigned char B_000E11D0[];
extern int B_000E19D0;
extern int B_000E19D4;
extern unsigned char B_000E19E0[];
extern int B_000E21E0;
extern void (*D_000414E0[])(Smfp *);
extern int DIntr(void);
extern int EIntr(void);
extern void Sg2ModMidiout(int, int, unsigned char *);

void Sg2SmfpTickProc(void)
{
    int enabled;
    Smfp *s;
    int i;
    int j;
    int beat[2];
    double t;
    unsigned long v;

    enabled = DIntr();
    s = B_000E0DC0;
    for (i = 0; i < 8; i++, s++) {
        B_000E19D0 = 0;
        B_000E19D4 = 0;
        B_000E11C0 = i;
        if (s->status != 2)
            continue;
        t = s->d48;
        beat[0] = (int)((double)(int)t / s->d38);
        s->d48 = t = t + s->d40;
        s->d58 = s->d58 + s->d78 / 100.0;
        beat[1] = (int)((double)(int)t / s->d38);
        if (beat[0] != beat[1]) {
            if (beat[1] != beat[0]) {
                s->x28++;
                if (s->x28 > s->x24) {
                    s->x28 = 1;
                    s->x2C++;
                }
            }
        }
        while (s->d48 - s->d50 >= 0) {
            if ((signed char)*s->p60 < 0)
                s->cmd = *s->p60++;
            D_000414E0[s->cmd >> 4](s);
            if (s->p60 == 0)
                break;
            v = 0;
            do {
                v = (v << 7) + (*s->p60 & 0x7F);
            } while (*s->p60++ & 0x80);
            s->d50 += v;
        }
        if (B_000E19D0 != 0)
            Sg2ModMidiout(s->mod, B_000E19D0, B_000E11D0);
    }
    if (B_000E21E0 != 0) {
        for (j = 0; j < B_000E21E0; j += B_000E19E0[j + 1] + 2)
            Sg2ModMidiout(B_000E19E0[j], B_000E19E0[j + 1], &B_000E19E0[j + 2]);
        B_000E21E0 = 0;
    }
    if (enabled)
        EIntr();
}


extern int B_000E11C4, B_000E11C8;
extern void *memset(void *p, int c, unsigned int n);
extern int Sg2CtrlEntryTickProcById(int id, void (*proc)(void));

int Sg2SmfpInit(int reserved)
{
    Smfp *s = B_000E0DC0;
    int i;

    for (i = 7; i >= 0; i--) {
        memset(s, -1, 0x80);
        s->status = 0;
        s++;
    }
    B_000E11C4 = 1;
    B_000E21E0 = 0;
    B_000E11C8 = 0;
    Sg2CtrlEntryTickProcById(0, Sg2SmfpTickProc);
    return 0;
}
