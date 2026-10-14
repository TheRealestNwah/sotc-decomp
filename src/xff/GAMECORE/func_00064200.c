extern char gcGlobalVar[];
extern int SCRGetFirstObj();
extern int torchObjRelease();

static int func_00064200(void)
{
    return torchObjRelease(SCRGetFirstObj((int)(gcGlobalVar + 0x2B0)));
}
