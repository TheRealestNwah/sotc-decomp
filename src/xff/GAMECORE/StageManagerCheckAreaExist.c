typedef struct {
    int pad0[2];
    unsigned int slot[37];
} StageArea;

typedef struct {
    char pad00[0x14];
    float cx;
    float cz;
    char pad1C[0x34 - 0x1C];
    int w;
    int h;
    int sw;
    int sh;
} StageGrid;

extern StageGrid *D_0017A868;
extern StageArea *D_0017A86C;
extern int D_0017A878;
extern int *DldSysUndefSymbol;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

int StageManagerCheckAreaExist(float *pos)
{
    StageGrid *g;
    StageArea *sl;
    float fx, fz;
    int ix, iz, sub, sx, sz;
    char *part;
    unsigned int v;
    int ret;

    if ((g = D_0017A868) == 0)
        goto one;
    if ((sl = D_0017A86C) == 0)
        goto one;
    fx = g->cx * g->w * 0.5f - pos[0];
    fz = pos[2] + g->cz * g->h * 0.5f;
    ix = fx / g->cx;
    iz = fz / g->cz;
    if (ix < 0 || iz < 0 || ix >= g->w || iz >= g->h)
        return 0;
    sx = (fx - ix * g->cx) / (g->cx / g->sw);
    sz = (fz - iz * g->cz) / (g->cz / g->sh);
    sub = sz * g->sw + sx;
    ret = 0;
    if (D_0017A878 == 0) {
        part = dldResolve(&sl[iz * g->w + ix].slot[0]);
        if (part != 0) {
            unsigned int w = *(unsigned int *)(part + sub * 0x3C + 4);
            v = ((w >> 2) & 1) | (w & 2);
        } else {
            v = 0;
        }
        if (v == 0)
            goto out;
    }
    ret = 1;
out:
    return ret;
one:
    return 1;
}
