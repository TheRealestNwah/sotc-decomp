typedef struct {
    int status;
    int a;
    int mod;
    int pad0C;
    int x10;
    int x14;
    int x18;
    int x1C;
    char pad20[0x10];
    double d30;
    double d38;
    double d40;
    char pad48[0x78 - 0x48];
    long d78;
} Smfp;

extern Smfp B_000E0DC0[];
extern int Sg2ModSetParam(int, int, int, int);
extern int Sg2CtrlGetTickMode(void);
extern long dpdiv(long, long);
extern long litodp(long);
extern long dpmul(long, long);
extern long dpadd(long, long);
typedef union { double d; long l; } DL;

#ifdef NONMATCHING /* 15 diffs */
int Sg2SmfpSetParam(int id, int param, int value, int arg)
{
    Smfp *s;
    int a, b;
    int x, y;
    DL t, d, r, m;
    int tick;

    if (id >= 0) {
    s = &B_000E0DC0[id];
    if (s->status == 0)
        return -1;
    switch (param) {
    case 2:
        B_000E0DC0[id].x10 = value;
        B_000E0DC0[id].x14 = value;
        Sg2ModSetParam(s->mod, 1, value, arg);
        break;
    case 0x8000:
        B_000E0DC0[id].x10 = value;
        B_000E0DC0[id].x14 = arg;
        Sg2ModSetParam(s->mod, 0x10000, value, arg);
        break;
    case 4:
        B_000E0DC0[id].x18 = value;
        Sg2ModSetParam(s->mod, param, value, arg);
        break;
    case 8:
        B_000E0DC0[id].x1C = value;
        Sg2ModSetParam(s->mod, param, value, arg);
        break;
    case 0x10:
        b = B_000E0DC0[id].x10;
        a = B_000E0DC0[id].x14;
        x = value;
        y = value;
        if (a < b)
            y = value * a / b;
        else if (b < a)
            x = value * b / a;
        B_000E0DC0[id].x10 = x;
        B_000E0DC0[id].x14 = y;
        Sg2ModSetParam(B_000E0DC0[id].mod, 0x100, value, arg);
        break;
    case 0x20:
        Sg2ModSetParam(s->mod, param, 1, 0);
        break;
    case 0x40:
        Sg2ModSetParam(s->mod, 0x20, 0, 0);
        break;
    case 0x80:
        Sg2ModSetParam(s->mod, 0x200, value, 0);
        break;
    case 0x100:
        Sg2ModSetParam(s->mod, 0x400, value, arg);
        break;
    case 0x200:
        s->d30 = B_000E0DC0[id].d30 = value;
        t.d = 1000000.0 / (60000000.0 / s->d30) * s->d38;
        tick = Sg2CtrlGetTickMode();
        d.l = litodp(tick);
        if (tick < 0)
            d.l = dpadd(d.l, 0x41F0000000000000);
        __asm__ __volatile__("");
        r.l = dpdiv(t.l, d.l);
        s->d40 = r.d;
        m.l = dpmul(r.l, s->d78);
        s->d40 = m.d / 100.0;
        break;
    case 0x400:
        Sg2ModSetParam(s->mod, 0x800, value, 0);
        break;
    case 0x800:
        Sg2ModSetParam(s->mod, 0x1000, value, 0);
        break;
    case 0x1000:
        Sg2ModSetParam(s->mod, 0x2000, value, arg);
        break;
    case 0x2000:
        Sg2ModSetParam(s->mod, 0x4000, value, arg);
        break;
    case 0x4000:
        Sg2ModSetParam(s->mod, 0x8000, value, arg);
        break;
    }
    }
    return 0;
}
#else
extern int Sg2SmfpSetParam(int id, int param, int value, int arg);
#endif
