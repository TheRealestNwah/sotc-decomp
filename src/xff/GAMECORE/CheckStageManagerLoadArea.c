extern int *DldSysUndefSymbol;

typedef struct {
    char pad0[0x34];
    int nx;
} AreaGrid;

typedef struct {
    char pad0[8];
    unsigned int h;
    char padC[0x90];
} AreaEnt;

typedef struct {
    int a;
    unsigned int flags;
    char pad8[0x34];
} AreaStage;

extern AreaGrid *D_0017A868;
extern AreaEnt *D_0017A86C;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

int CheckStageManagerLoadArea(int x, int z, int k)
{
    AreaStage *s;
    unsigned int f;

    if (D_0017A868 != 0 && D_0017A86C != 0) {
        s = (AreaStage *)dldResolve(&D_0017A86C[z * D_0017A868->nx + x].h);
        if (s != 0) {
            f = s[k].flags;
            return ((f >> 2) & 1) | (f & 2);
        }
    }
    return 0;
}
