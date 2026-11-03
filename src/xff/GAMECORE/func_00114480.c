extern int *DldSysUndefSymbol;
static inline int *dldPtr(unsigned int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol)
               ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)
               : 0;
}
extern char *GetCharacterClass(void *);

static int func_00114480(void *obj, unsigned int *h)
{
    char *cc = GetCharacterClass(obj);
    unsigned int *list = (unsigned int *)dldElem(h);
    int *t;
    int n;
    int i;

    if (list == 0) {
        return 1;
    }
    t = dldPtr(h);
    n = (t != 0 && t != DldSysUndefSymbol) ? t[3] : 0;
    for (i = 0; i < n; i++) {
        if (*(char **)(cc + 0x750) == dldElem(list + i)) {
            return 1;
        }
    }
    return 0;
}
