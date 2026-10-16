extern int DldSysUndefSymbol;
extern char *getSCRDataCtrlWork(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void createEyeWork(void *o, unsigned int *h)
{
    int *w = (int *)(getSCRDataCtrlWork(o) + 0x4100);
    char *p = dldResolve(h);
    char *q;
    int i;

    w[1] = 0;
    w[2] = 0;
    w[0] = (int)p;
    q = (char *)(w + 4);
    for (i = 0; i < 5; i++) {
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(q) : "memory");
        q += 0x10;
    }
}
