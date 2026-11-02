extern int DldSysUndefSymbol;
extern int stagemanager_checkstageAlreadyLoadedByStrptr(unsigned int *);

static inline char *dldTarget(unsigned int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(char **)((char *)h - off) : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

int finishLoadMotList(unsigned int *h)
{
    unsigned int *list = (unsigned int *)dldResolve(h);

    if (list == 0)
        return 1;
    if (dldTarget(list) == 0)
        return 0;
    while (dldTarget(list) != 0) {
        if (stagemanager_checkstageAlreadyLoadedByStrptr(list) == 0)
            return 0;
        list++;
    }
    return 1;
}
