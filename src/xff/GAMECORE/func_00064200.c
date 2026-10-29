extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern void torchObjRelease(void *);

static void func_00064200(void)
{
    torchObjRelease(SCRGetFirstObj(gcGlobalVar + 0x2B0));
}
