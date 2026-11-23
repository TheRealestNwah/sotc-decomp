/* Parked attempt, 17 diffs, same size. Blends two poses field by field (out = wa * a + wb * b), with the angle at 0x40 wrapped through 360 and the fields at 0x7C/0x80 blended only when both are positive and b's is not 0.001. Remaining: register allocation in the angle block; the Original loads b->ang first and keeps both copies (x in f1, y in f6, d in f2), ours loads a->ang first and swaps f2/f4/f5. A 30-minute permuter run found nothing better. */
#ifdef NONMATCHING
typedef struct {
    int k;
    float a[15];
    float ang;
    float b[14];
    float c;
    float d;
} Pose;

static inline float angBlend(float wa, float pa, float wb, float pb)
{
    float x;
    float y;
    float d;
    float r;

    y = pa;
    x = pb;
    d = x - y;
    if ((d < 0.0f) ? (-180.0f <= d) : (d <= 180.0f)) {
        r = wa * pa + wb * pb;
    } else {
        if (pa < 0.0f)
            y = pa + 360.0f;
        else if (pb < 0.0f)
            x = pb + 360.0f;
        r = wa * y + wb * x;
        if (180.0f < r)
            r -= 360.0f;
    }
    return r;
}

static void func_000EFD90(Pose *out, float wa, Pose *a, float wb, Pose *b, void *x)
{
    out->a[0] = wa * a->a[0] + wb * b->a[0];
    out->a[1] = wa * a->a[1] + wb * b->a[1];
    out->a[2] = wa * a->a[2] + wb * b->a[2];
    out->a[3] = wa * a->a[3] + wb * b->a[3];
    out->a[4] = wa * a->a[4] + wb * b->a[4];
    out->a[5] = wa * a->a[5] + wb * b->a[5];
    out->a[6] = wa * a->a[6] + wb * b->a[6];
    out->a[7] = wa * a->a[7] + wb * b->a[7];
    out->a[8] = wa * a->a[8] + wb * b->a[8];
    out->a[9] = wa * a->a[9] + wb * b->a[9];
    out->a[10] = wa * a->a[10] + wb * b->a[10];
    out->a[11] = wa * a->a[11] + wb * b->a[11];
    out->a[12] = wa * a->a[12] + wb * b->a[12];
    out->a[13] = wa * a->a[13] + wb * b->a[13];
    out->a[14] = wa * a->a[14] + wb * b->a[14];
    out->ang = angBlend(wa, a->ang, wb, b->ang);
    out->b[0] = wa * a->b[0] + wb * b->b[0];
    out->b[1] = wa * a->b[1] + wb * b->b[1];
    out->b[2] = wa * a->b[2] + wb * b->b[2];
    out->b[3] = wa * a->b[3] + wb * b->b[3];
    out->b[4] = wa * a->b[4] + wb * b->b[4];
    out->b[5] = wa * a->b[5] + wb * b->b[5];
    out->b[6] = wa * a->b[6] + wb * b->b[6];
    out->b[7] = wa * a->b[7] + wb * b->b[7];
    out->b[8] = wa * a->b[8] + wb * b->b[8];
    out->b[9] = wa * a->b[9] + wb * b->b[9];
    out->b[10] = wa * a->b[10] + wb * b->b[10];
    out->b[11] = wa * a->b[11] + wb * b->b[11];
    out->b[12] = wa * a->b[12] + wb * b->b[12];
    out->b[13] = wa * a->b[13] + wb * b->b[13];
    if (0.0f < a->c && 0.0f < b->c && b->c != 0.001f)
        out->c = wa * a->c + wb * b->c;
    if (0.0f < a->d && 0.0f < b->d && b->d != 0.001f)
        out->d = wa * a->d + wb * b->d;
}
#endif
