extern void *memset(void *, int, unsigned int);
extern void GexInitCommonFunc(void *, void *, void *, void *, void *, float *);

void GexCeilInitFunc(void *a, void *b, void *c, void *d, void *e)
{
    float v[4];
    memset(v, 0, 0x10);
    v[1] = 1.0f;
    GexInitCommonFunc(a, b, c, d, e, v);
}
