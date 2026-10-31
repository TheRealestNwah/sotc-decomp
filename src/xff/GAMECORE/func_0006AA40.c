extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetSCRCharaAIWorkPtr(void *);

static void func_0006AA40(void)
{
    void *obj = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    char *work;

    if (obj != 0) {
        work = GetSCRCharaAIWorkPtr(obj);
        if (*(int *)(work + 0x41E0) > 0) {
            *(int *)(work + 0x41E0) -= 1;
        }
    }
}
