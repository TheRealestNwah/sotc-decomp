extern int *DldSysUndefSymbol;
extern int stagemanager_checkstageAlreadyLoadRequestedByStrptr(unsigned int *);
extern void stagemanager_loadstageByStrptrWithTargetObjectAreaCenter(unsigned int *, void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline int *dldSymbol(unsigned int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

void loadRequestMotList(void *object, unsigned int *handle)
{
    unsigned int *list = (unsigned int *)dldResolve(handle);

    if (list == 0)
        return;
    if (dldSymbol(list) == 0)
        return;
    for (; dldSymbol(list) != 0; list++) {
        if (!stagemanager_checkstageAlreadyLoadRequestedByStrptr(list))
            stagemanager_loadstageByStrptrWithTargetObjectAreaCenter(list, object);
    }
}
