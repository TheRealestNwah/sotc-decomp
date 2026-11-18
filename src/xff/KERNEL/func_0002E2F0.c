typedef struct {
    short *buf;
    float *out;
    int len;
    int pad;
    int pos;
} Dsp;

typedef struct {
    int flags;
    Dsp dsp;
    char pad18[0x1A0 - 0x18];
    int opt;
    int mode;
    int loop;
    int pad1AC[3];
    int a;
    int b;
    int pad1C0;
    unsigned int period;
    int c;
    int d;
    unsigned int phase;
} Voice;

extern void func_0002DE30(Dsp *b, int n, int x, int y);
extern void func_0002DEF0(Dsp *b, int n, int x, int y, int lo, int hi);
extern void func_0002DF98(Dsp *b, int n, int x, int y);
extern void func_0002E068(Dsp *b, int n, int x, int y, int lo, int hi);
extern void func_0002E150(Dsp *b, int n);
extern void func_0002E1B0(Dsp *b, int n);

static void func_0002E2F0(Voice *v, int n)
{
    Dsp *d = &v->dsp;
    int len = d->len;
    int pos = d->pos;
    if (v->opt & 2) {
        if (pos + n >= len) {
            n = len - pos;
            v->flags = 2;
        }
    }
    switch (v->mode) {
    case 0:
        if (!v->c && !v->d)
            func_0002DE30(d, n / 2, v->a, v->b);
        else
            func_0002DEF0(d, n / 2, v->a, v->b, v->c, v->d);
        break;
    case 1:
        if (v->c || v->d)
            func_0002E068(d, n, v->a, v->b, v->c, v->d);
        else
            func_0002DF98(d, n, v->a, v->b);
        break;
    }
    if (v->mode == 1 && v->loop == 0)
        func_0002E150(d, n);
    func_0002E1B0(d, n);
    if (v->period) {
        if (v->mode == 0)
            n /= 2;
        v->phase += n;
        v->phase %= v->period / 2;
    }
}
