extern int *DldSysUndefSymbol;

typedef struct { int w[0x48 / 4]; } A48;
typedef struct { int w[0x194 / 4]; } A194;
typedef struct { int w[0xCC / 4]; } ACC;
typedef struct { int w[0x84 / 4]; } A84;
typedef struct { int w[0xD0 / 4]; } AD0;
typedef struct { int w[0xE4 / 4]; } AE4;
typedef struct { int w[0x8C / 4]; } A8C;
typedef struct {
    void *head;
    A48 a;
    A194 b;
    ACC c;
    A84 d;
    AD0 e;
    AE4 f;
    AE4 g;
    A8C h;
} CamParam;

typedef struct {
    int pad0[5];
    unsigned int *b;
    int pad18;
    unsigned int *c;
    int pad20;
    unsigned int *d;
    int pad28;
    unsigned int *e;
    int pad30;
    unsigned int *f;
    int pad38;
    unsigned int *g;
    int pad40;
    unsigned int *h;
} CamSrc;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static void func_000EDCA8(CamParam *dst, CamSrc *src)
{
    dst->head = src;
    dst->a = *(A48 *)src;
    dst->b = *(A194 *)dldResolve(src->b);
    dst->c = *(ACC *)dldResolve(src->c);
    dst->d = *(A84 *)dldResolve(src->d);
    dst->e = *(AD0 *)dldResolve(src->e);
    dst->f = *(AE4 *)dldResolve(src->f);
    dst->g = *(AE4 *)dldResolve(src->g);
    dst->h = *(A8C *)dldResolve(src->h);
}
