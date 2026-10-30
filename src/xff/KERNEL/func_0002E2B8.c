typedef struct {
    int pad0;
    float *data;
} FloatBuf;

static void func_0002E2B8(FloatBuf *dst, FloatBuf *src, int n)
{
    float *d = dst->data;
    float *s = src->data;
    int i;

    for (i = 0; i < n; i++)
        *d++ += *s++;
}
