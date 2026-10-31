extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *list);
extern char *GetSCRCharaAIWorkPtr(void *);

static void func_0006BED0(void)
{
    void *obj;

    obj = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    if (obj != 0) {
        *(int *)(GetSCRCharaAIWorkPtr(obj) + 0x41EC) = 1;
    }
}
