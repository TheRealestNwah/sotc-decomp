extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);
extern void func_000CDEB0(void *, int);

void mapLogReset(void)
{
    void *o = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    char *l;
    if (o == 0)
        return;
    l = GetLayoutClass(o);
    if (l == 0)
        return;
    func_000CDEB0(*(void **)(l + 0x134), 1);
}
