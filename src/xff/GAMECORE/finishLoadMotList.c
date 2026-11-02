extern int *DldSysUndefSymbol;
extern int stagemanager_checkstageAlreadyLoadedByStrptr(unsigned int *name);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline char *dldPtr(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(char **)((char *)h - off) : 0;
}

int finishLoadMotList(unsigned int *h)
{
    unsigned int *p = (unsigned int *)dldElem(h);

    if (p == 0)
        return 1;
    if (dldPtr(p) == 0)
        return 0;
    while (dldPtr(p) != 0) {
        if (!stagemanager_checkstageAlreadyLoadedByStrptr(p))
            return 0;
        p++;
    }
    return 1;
}
