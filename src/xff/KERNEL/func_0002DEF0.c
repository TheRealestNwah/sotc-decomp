typedef struct {
    short *buf;
    float *out;
    int len;
    int pad;  /* +0xC */
    int pos;
} Dsp;

/* Mono looping variant: pos wraps from hi back to lo. */
static void func_0002DEF0(Dsp *s, int n, int l, int r, int lo, int hi)
{
    float *o = s->out;
    float *o2 = o + 256;
    short *b = s->buf;
    int pos = s->pos;
    int k;
    int c;
    for (k = 0; k < n; k += 256) {
        for (c = 255; c >= 0; c--) {
            int v = b[pos];
            pos++;
            if (hi < pos)
                pos = lo;
            *o++ = (float)(v * l / 100);
            *o2++ = (float)(v * r / 100);
        }
        o += 256;
        o2 += 256;
    }
    s->pos = pos;
}
