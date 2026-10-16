extern int *DldSysUndefSymbol;
extern void setAttainRangeStruct(void *, float *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void setSCRAttainRange(void *w, unsigned int *h)
{
    float *p = (float *)dldResolve(h);
    float r[8];

    if (p == 0)
        return;
    r[0] = p[0];
    r[1] = p[1];
    r[2] = p[2];
    r[3] = 1.0f;
    r[4] = p[3];
    r[5] = p[4];
    r[6] = p[5] * 0.0174532933f;
    r[7] = p[6];
    setAttainRangeStruct(w, r);
}
