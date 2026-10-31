extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetSCRCharaAIWorkPtr(void *);

static void func_000CB608(void)
{
    void *obj = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    char *work;

    if (obj != 0) {
        work = GetSCRCharaAIWorkPtr(obj);
        if (*(int *)(work + 0x41D8) == 0 && *(int *)(work + 0x41C8) > 0) {
            *(int *)(work + 0x41C8) -= 1;
        }
    }
}
