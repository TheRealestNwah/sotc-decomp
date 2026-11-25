#ifdef NONMATCHING /* 9 diffs: float register allocation in the grid-position block */
extern int DldSysUndefSymbol;
extern char _GameObject[];
typedef int Q __attribute__((mode(TI)));
extern Q ZeroPoint;
typedef struct { char pad[0x14]; float w; float d; char pad2[0x18]; int nx; int nz; } Layout;
extern Layout *D_0017A868;
extern char *GetLayoutClass(int);
extern int func_00026238(int, void *, void *, int, int);
extern void gStatSetGObjAdrs(int, int);
extern void unloadObj(int);

typedef struct { int a; int h; char pad[0x40]; int done; } Elem;
typedef struct { char pad[8]; int obj; char pad2[4]; int h; } Ent;
typedef struct { char pad[8]; char *type; int n; Ent *ents; } GObj;

static inline int *dldTable(int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline int dldElem(int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[4] + ((*(unsigned *)h >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int *dldObj(int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t : 0;
}

void initlayout(int a0, int *h, int idx, int unused, int arg4, int flag)
{
    float v[4] __attribute__((aligned(16)));
    int *t;
    int n, i, j, k, l, m, m2, j2, any;
    Elem *base, *e;

    t = dldTable(h);
    n = (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;
    if (n == 0)
        return;
    base = (Elem *)dldElem(h);
    if (idx >= 0) {
        Layout *L = D_0017A868;

        v[0] = -(((idx % L->nx) - L->nx * 0.5f) * L->w + L->w * 0.5f);
        v[1] = 0;
        v[2] = ((idx / L->nx) - (float)L->nz * 0.5f) * L->d + L->d * 0.5f;
        v[3] = 1.0f;
    } else {
        *(Q *)v = ZeroPoint;
    }
    if (flag) {
        for (e = base, i = 0; i < n; i++, e++) {
            if (((GObj *)dldObj(&e->h))->type == _GameObject) {
                GObj *g = (GObj *)dldObj(&e->h);
                Ent *p = g->ents;

                for (m = g->n, j = 0; j < m; j++, p++) {
                    if (p->obj) {
                        char *c = GetLayoutClass(p->obj);
                        if (c)
                            *(int *)(c + 0x190) = 0;
                    }
                }
                p = g->ents;
                for (m2 = g->n, j2 = 0; j2 < m2; j2++, p++) {
                    int o = dldElem(&p->h);
                    if (p->obj) {
                        unloadObj(p->obj);
                        p->obj = 0;
                    }
                    if (o)
                        gStatSetGObjAdrs(o, 0);
                }
            }
            e->done = 0;
        }
    }
    for (e = base, k = 0; k < n; k++, e++)
        func_00026238(a0, e, v, 0, arg4);
    do {
        any = 0;
        for (e = base, l = 0; l < n; l++, e++)
            if (e->done == 0)
                any |= func_00026238(a0, e, &ZeroPoint, 1, arg4);
    } while (any);
}
#else
extern void initlayout(int a0, int *h, int idx, int unused, int arg4, int flag);
#endif
