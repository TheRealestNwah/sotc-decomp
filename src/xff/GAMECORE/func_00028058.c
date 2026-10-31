typedef struct {
    char pad0[0x14];
    float width;
    float depth;
    char pad1C[0x18];
    int columns;
    int rows;
    int subColumns;
    int subRows;
} StageGrid;

typedef struct {
    int pad0[2];
    unsigned int slot[37];
} StageArea;

extern StageGrid *D_0017A868;
extern StageArea *D_0017A86C;
extern int D_0017A874;
extern int *DldSysUndefSymbol;
extern int getstagenumber(int);

static inline int *dldTarget(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (int *)t[3] : 0;
}

static int func_00028058(void *unused, int x, int z)
{
    StageGrid *s = D_0017A868;
    int nx, nz, area, part;

    if (z < 0)
        z = 0;
    if (x < 0)
        x = 0;
    nz = (int)(s->depth * (float)s->rows / (s->depth / (float)s->subRows)) - 1;
    if (z < nz)
        nz = z;
    nx = (int)(s->width * (float)s->columns / (s->width / (float)s->subColumns)) - 1;
    if (x < nx)
        nx = x;
    {
        int ax = nx / s->subColumns, px = nx % s->subColumns;
        int az = nz / s->subRows, pz = nz % s->subRows;

        area = az * s->columns + ax;
        part = pz * s->subColumns + px;
    }
    if (dldTarget(&D_0017A86C[area].slot[D_0017A874]) != 0) {
        area <<= 5;
        area |= part & 0x1F;
        return (getstagenumber(area) << 15) | area;
    }
    return -1;
}
