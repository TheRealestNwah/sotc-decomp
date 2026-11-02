extern int *DldSysUndefSymbol;
extern int GetSCRCharaAIWorkPtr(void);
extern int stagemanager_checkstageAlreadyLoadedByStrptr(unsigned int *);
extern void setLoadingCheckFunc(int, int);
extern void scrRun(void);
extern void finishLoadMotList(void);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol)
               ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)
               : 0;
}

static inline char *dldStr(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(char **)((char *)h - off) : 0;
}

static inline int allLoaded(unsigned int *p)
{
    if (p == 0)
        return 1;
    if (dldStr(p) != 0) {
        while (dldStr(p) != 0) {
            if (!stagemanager_checkstageAlreadyLoadedByStrptr(p))
                return 0;
            p++;
        }
        return 1;
    }
    return 0;
}

void checkDeadMotionLoadByScriptDataSystem(void)
{
    char *w = (char *)((GetSCRCharaAIWorkPtr() + 0x13) & ~0xF);
    unsigned int *p = (unsigned int *)dldElem(*(unsigned int **)(w + 0x4180));

    if (allLoaded(p))
        return;
    setLoadingCheckFunc((int)finishLoadMotList, *(int *)(w + 0x4180));
    scrRun();
}
