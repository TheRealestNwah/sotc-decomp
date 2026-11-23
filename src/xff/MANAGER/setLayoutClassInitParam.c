extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}
typedef struct {
    int w0, w4, w8, wC, w10, w14;
    float w18;
    int w1C, w20, w24, w28, w2C, w30, w34;
} LayoutInfoS;
typedef union { LayoutInfoS s; int i[14]; } LayoutInfo;
typedef struct {
    int name;
    int one;
    int geo;
    void *mdl;
    int col;
    void *grp;
    int w18, w1C;
    void *w20;
    int w24, w28, w2C, w30, w34, w38, w3C, w40, w44, w48, w4C;
    float w50;
    int w54, w58, w5C;
    void *disp;
    int w64;
    void *clip;
    void *light;
    int w70, w74, w78;
} LayoutInitParam;
extern void DispLayoutObjModel();
extern void ClipLayoutObjModel();
extern void CalcLightLayoutObj();

void setLayoutClassInitParam(LayoutInitParam *out, int name, int a2, int *def, LayoutInfo *info)
{
    LayoutInitParam r;
    LayoutInitParam p;
    int geo = 0;
    int col = 0;
    void *mdl;
    void *grp;
    void *e;
    int f;

    if (def != 0) {
        name = def[0];
        e = dldElement(def + 1);
        geo = 0;
        if (e != 0) geo = *(int *)((char *)e + 8);
        e = dldElement(def + 3);
        col = 0;
        if (e != 0) col = *(int *)((char *)e + 8);
        mdl = dldElement(def + 2);
    } else {
        mdl = 0;
    }
    grp = def != 0 ? dldElement(def + 4) : 0;
    p.name = name;
    p.col = col;
    p.one = 1;
    p.geo = geo;
    p.mdl = mdl;
    p.grp = grp;
    p.w18 = 0;
    p.w1C = 0;
    p.w20 = def != 0 ? dldElement(def + 5) : 0;
    p.w24 = info->s.w20;
    p.w28 = info->s.w0;
    p.w2C = info->s.w4;
    p.w30 = info->s.w8;
    p.w34 = info->s.wC;
    p.w38 = info->s.w2C;
    f = -1;
    if (grp == 0) {
        f = info->s.w34;
        if (geo != 0 || mdl != 0) f |= 6;
    }
    p.w3C = f;
    p.w40 = info->s.w10;
    p.w44 = 0;
    p.w48 = 0;
    p.w4C = info->s.w14;
    p.w50 = info->s.w18;
    p.w54 = info->s.w24;
    p.w58 = 0;
    p.w5C = 0;
    p.disp = DispLayoutObjModel;
    p.w64 = 0;
    p.clip = ClipLayoutObjModel;
    p.light = CalcLightLayoutObj;
    p.w70 = 0;
    p.w74 = info->s.w28;
    p.w78 = 0;
    r = p;
    *out = r;
}
