extern int *DldSysUndefSymbol;

typedef void (*SCRBaseFunc)(void *, int, int, float, float, float, float, long, long, int *, int *, int *, int *);

typedef struct {
    SCRBaseFunc func;
    int a;
    int b;
    float f0;
    float f1;
    float f2;
    float f3;
    int pad;
    long l0;
    long l1;
    int p0;
    int p1;
    int p2;
    int p3;
} SCRBaseEntry;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void execSCRBaseFunc(void *actor, unsigned int *h)
{
    SCRBaseEntry *e = (SCRBaseEntry *)dldResolve(h);

    SCRBaseFunc f;

    if (e != 0) {
        while (e->func != 0) {
            f = e->func;
            f(actor, e->a, e->b, e->f0, e->f1, e->f2, e->f3, e->l0, e->l1, &e->p0, &e->p1, &e->p2, &e->p3);
            e++;
        }
    }
}
