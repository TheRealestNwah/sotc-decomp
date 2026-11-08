typedef struct {
    char pad00[0x1C];
    float x2;
    float x1;
    float y2;
    float y1;
    char pad2C[0x8];
    float b0;
    float b1;
    float b2;
    float a1;
    float a2;
} Iir;

void IirFilter(Iir *f, int n, float *buf)
{
    float x[3];
    float b0 = f->b0;
    float b1 = f->b1;
    float b2 = f->b2;
    float a1 = f->a1;
    float a2 = f->a2;
    int i;

    x[0] = buf[0];
    x[1] = buf[1];
    x[2] = buf[2];
    buf[0] = b0 * x[0] + b1 * f->x1 + b2 * f->x2 - a1 * f->y1 - a2 * f->y2;
    buf[1] = b0 * x[1] + b1 * x[0] + b2 * f->x1 - a1 * buf[0] - a2 * f->y1;
    for (i = 2; i < n; i++) {
        buf[i] = b0 * x[2] + b1 * x[1] + b2 * x[0] - a1 * buf[i - 1] - a2 * buf[i - 2];
        x[0] = x[1];
        x[1] = x[2];
        x[2] = buf[i + 1];
    }
    f->x2 = x[0];
    f->x1 = x[1];
    f->y2 = buf[n - 2];
    f->y1 = buf[n - 1];
}
