typedef struct {
    short *buf;
    float *out;
} Dsp;

/* Downmix: average the L and R blocks (256 floats each) into both. */
static void func_0002E150(Dsp *s, int n)
{
    float *o = s->out;
    int i;
    for (i = 0; i < n;) {
        float *l = (float *)(i * 4 + (int)o);
        float *r;
        float m;
        i++;
        r = l + 256;
        if (i & 0x100)
            i += 0x100;
        m = (*l + *r) * 0.5f;
        *r = m;
        *l = m;
    }
}
