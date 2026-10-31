extern int *DldSysUndefSymbol;

typedef struct {
    char pad0[0x44];
    unsigned int listA;
    unsigned int listB;
} SheetPair;

extern void func_00022980(char *);
extern void func_00022CD0(char *);

static inline int *dldSheet(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return t;
}

static inline char *dldData(unsigned int *h)
{
    int *t = dldSheet(h);

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
}

static inline int dldCount(unsigned int *h)
{
    int *t = dldSheet(h);

    return (t != 0 && t != DldSysUndefSymbol) ? t[3] : 0;
}

static void func_00022EF8(SheetPair *p)
{
    char *a = dldData(&p->listA);
    char *b = dldData(&p->listB);
    int na = dldCount(&p->listA);
    int nb = dldCount(&p->listB);
    int i;

    for (i = 0; i < na; i++)
        func_00022980(a + i * 0x14);
    for (i = 0; i < nb; i++)
        func_00022CD0(b + i * 0x14);
}
