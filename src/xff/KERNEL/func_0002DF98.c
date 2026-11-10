typedef struct {
    short *buf;
    float *out;
    int len;
    int pad;  /* +0xC */
    int pos;
} Dsp;

/* Block-interleaved stereo (256 L then 256 R) -> float channels. */
static void func_0002DF98(Dsp *s, int n, int l, int r)
{
    int pos = s->pos;
    short *p = s->buf + pos;
    float *o = s->out;
    int k;
    int c;
    for (k = 0; k < n; k += 512) {
        for (c = 0; c < 256; c++)
            *o++ = (float)(*p++ * l / 100);
        for (c = 0; c < 256; c++)
            *o++ = (float)(*p++ * r / 100);
    }
    s->pos = pos + n;
    if (s->pos >= s->len)
        s->pos = 0;
}
