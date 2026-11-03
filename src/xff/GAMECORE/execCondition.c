extern int DldSysUndefSymbol;

typedef int (*CondFunc)(void *, int, int, int, float, float, float, long, long, long, void *, void *, void *);

typedef struct {
    int mode;
    int result;
    CondFunc func;
    int a1;
    int a2;
    int a3;
    float f0;
    float f1;
    float f2;
    int pad24;
    long l0;
    long l1;
    long l2;
    int p40;
    int p44;
    int p48;
    int pad4C;
} Cond;

static inline char *DldGetPtr(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

int execCondition(void *obj, unsigned int *h)
{
    Cond *c;
    CondFunc fn;

    c = (Cond *)DldGetPtr(h);
    if (c == 0)
        return 1;

    if (c->mode == 1) {
        for (; c->func != 0; c++) {
            fn = c->func;
            if (c->result != fn(obj, c->a1, c->a2, c->a3, c->f0, c->f1, c->f2, c->l0, c->l1, c->l2, &c->p40, &c->p44, &c->p48))
                return 0;
        }
        return 1;
    }
    if (c->mode == 2) {
        for (; c->func != 0; c++) {
            fn = c->func;
            if (c->result == fn(obj, c->a1, c->a2, c->a3, c->f0, c->f1, c->f2, c->l0, c->l1, c->l2, &c->p40, &c->p44, &c->p48))
                return 1;
        }
        return 0;
    }
    return 0;
}
