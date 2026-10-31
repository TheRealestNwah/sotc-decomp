extern char gcGlobalVar[];
extern int *DldSysUndefSymbol;
extern void *SCRGetFirstObj(void *);

int SCRConditionBossCheck(int a0, int a1, int a2, int a3, int t0, int t1, int t2, unsigned int *ref)
{
    void *obj;
    int off;
    int *t;
    char *p;

    obj = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    off = *ref & 0x3FFFF;
    t = off != 0 ? *(int **)((char *)ref - off) : 0;
    p = (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
    if (obj == 0 || p == 0)
        return 0;
    return *(void **)(p + 8) == obj;
}
