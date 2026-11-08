typedef struct {
    unsigned int now;
    unsigned int old;
    unsigned int trig;
    unsigned int rel;
    unsigned int rep;
    float time[16];
    unsigned char lx, ly, rx, ry;
    struct Shock { char d[0x10]; unsigned char m0, m1; char pad[2]; } shock;
    char motor[4];
    char acr[8];
} PadData;

typedef struct {
    char pad0[0x104];
    unsigned char b0, b1;
    unsigned char rx, ry, lx, ly;
    char pad10A[0x118 - 0x10A];
    int vib;
} PadSys;

extern PadData iosDefaultPadData[];
extern void (*D_000407F8)(void);
extern int iosGetTCountExtension(void);
extern float iosGetSecondFromTCount(int);
extern void padSysTickProc(void);
extern PadSys *padSysGet(int, int);
extern void Shock_Decode(void *, void *, void *);
extern void Shock_SetMotor(int, int, void *, int, int);
extern void padSysVibSetAcrParam(void *, void *);

/* Parked: Parked: 85 words differ (button word kept in a register instead of reloading trig each loop pass) */
#ifdef NONMATCHING
void iosPadTickProc(void)
{
    int port;
    float now = iosGetSecondFromTCount(iosGetTCountExtension());

    padSysTickProc();
    for (port = 0; port < 2; port++) {
        PadData *p = &iosDefaultPadData[port];
        PadSys *s = padSysGet(port, 0);
        unsigned int btn, chg;
        int i;
        float *tp;
        struct Shock *sh;

        p->old = p->now;
        btn = (s->b0 << 8) | s->b1;
        p->rep = 0;
        chg = btn ^ p->old;
        p->trig = chg & btn;
        p->rel = chg & ~btn;
        p->now = btn;
        tp = p->time;
        for (i = 0; i < 16; i++, tp++) {
            unsigned int bit = 1 << i;
            float t;
            if (p->trig & bit) {
                t = now + 0.4f;
            } else if ((p->now & bit) && *tp < now) {
                t = now + 0.08f;
            } else {
                continue;
            }
            *tp = t;
            p->rep |= bit;
        }
        p->rx = s->rx;
        p->ry = s->ry;
        p->lx = s->lx;
        p->ly = s->ly;
        sh = &p->shock;
        Shock_Decode(sh, &p->shock.m0, &p->shock.m1);
        if (s->vib == 1) {
            Shock_SetMotor(sh->m0, sh->m1, p->motor, port, 0);
            padSysVibSetAcrParam(s, p->acr);
        }
    }
    if (D_000407F8 != 0) {
        D_000407F8();
    }
}
#else
extern void iosPadTickProc(void);
#endif
