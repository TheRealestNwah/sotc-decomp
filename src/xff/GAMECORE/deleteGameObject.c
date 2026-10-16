extern int *DldSysUndefSymbol;
extern void unloadObj(void *);
extern void gStatSetGObjAdrs(void *, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

typedef struct {
    int a;
    int b;
    void *obj;
    int c;
    unsigned int h;
} GObjEnt;

void deleteGameObject(char *g)
{
    int n = *(int *)(g + 0xC);
    GObjEnt *e = *(GObjEnt **)(g + 0x10);
    int i;

    for (i = 0; i < n; i++, e++) {
        char *p = dldResolve(&e->h);

        if (e->obj != 0) {
            unloadObj(e->obj);
            e->obj = 0;
        }
        if (p != 0)
            gStatSetGObjAdrs(p, 0);
    }
}
