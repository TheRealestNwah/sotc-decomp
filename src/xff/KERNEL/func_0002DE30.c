typedef struct {
    short *buf;
    float *out;
    int len;
    int pad;  /* +0xC */
    int pos;
} Dsp;

/* Mono 16-bit PCM -> two float channels (blocks of 256), volumes in percent. */
static void func_0002DE30(Dsp *s, int n, int l, int r)
{
    int pos = s->pos;
    float *o = s->out;
    short *b = s->buf + pos;
    float *o2 = o + 256;
    int k;
    int c;
    for (k = 0; k < n;) {
        for (c = 255; c >= 0; c--) {
            int v = b[k];
            k++;
            *o++ = (float)(v * l / 100);
            *o2++ = (float)(v * r / 100);
        }
        o += 256;
        o2 += 256;
    }
    s->pos = pos + n;
    if (s->pos >= s->len)
        s->pos = 0;
}
