extern int func_000B1380(void *, float *, float *, void *, int *, void *);
extern int func_000B1208(void *, float *, float *, void *, int *, void *);

static int func_000B69F0(void *a, float *b, float *c, void *d, int *e, void *f)
{
    int hit;
    int i = e[1] & 3;

    if (b[i] >= c[i]) {
        hit = 0;
        if (func_000B1380(a, b, c, d, e, f) || func_000B1208(a, b, c, d, e, f)) {
            hit = 1;
        }
    } else {
        hit = 0;
        if (func_000B1208(a, b, c, d, e, f) || func_000B1380(a, b, c, d, e, f)) {
            hit = 1;
        }
    }
    return hit;
}
