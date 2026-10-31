extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *list);
extern char *GetSCRCharaAIWorkPtr(void *);

static void func_00062FD8(void)
{
    void *obj;
    char *w;

    obj = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    if (obj != 0) {
        w = GetSCRCharaAIWorkPtr(obj);
        if (*(int *)(w + 0x41B0) > 0) {
            *(int *)(w + 0x41B0) -= 1;
        }
    }
}
