extern int *DldSysUndefSymbol;
static inline int resourceCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? t[3] : 0;
}
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}
extern int strcmp(const char *, const char *);
int SearchJudgeVolumeByName(unsigned int *resource, const char *name)
{
    int count = resourceCount(resource);
    const char **names = (const char **)dldResolve(resource);
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(names[i], name) == 0)
            return i;
    }
    return -1;
}
