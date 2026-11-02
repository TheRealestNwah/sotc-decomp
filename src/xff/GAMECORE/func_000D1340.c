extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);
extern void func_000CDEB0(void *, int);
extern void scrRun(void);

static void func_000D1340(void)
{
    void *obj;
    char *l;

    for (;;) {
        obj = SCRGetFirstObj(gcGlobalVar + 0x2B0);
        if (obj != 0) {
            l = GetLayoutClass(obj);
            if (l != 0) {
                func_000CDEB0(*(void **)(l + 0x134), 0);
            }
        }
        scrRun();
    }
}
