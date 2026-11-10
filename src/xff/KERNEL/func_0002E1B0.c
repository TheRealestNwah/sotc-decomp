#ifdef NONMATCHING
/* Parked: 15 words differ. The original hoists the `lw x` into the beqz delay slot,
   which a volatile local can't reproduce; without volatile the stack slot
   disappears. */
typedef struct Iir Iir;
extern void IirFilter(Iir *f, int n, float *buf);

typedef struct {
    int on;
    char pad[0x34 - 0x4];
    char l[0x48];
    char r[0x48];
} Chan; /* 0xC4 */

typedef struct {
    short *buf;
    float *out;
    int len;
    int pad;
    int pos;
    Chan ch[2];
} Dsp;

static void func_0002E1B0(Dsp *s, int n)
{
    struct { volatile int x; volatile int m; } L;
    int i;
    L.m = n < 0 ? n + 511 : n;
    for (i = 0; i < 2; i++) {
        if (s->ch[i].on) {
            float *p;
            int k, j;
            int t = L.x;
            Iir *l, *r;
            if (!(i ^ 1))
                t = 0;
            k = L.m >> 9;
            L.x = t;
            l = (Iir *)s->ch[i].l;
            r = (Iir *)s->ch[i].r;
            p = s->out;
            for (j = 0; j < k; j++) {
                IirFilter(l, 256, p);
                p += 256;
                IirFilter(r, 256, p);
                p += 256;
            }
        }
    }
}
#endif
