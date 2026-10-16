extern char gcGlobalVar[];
extern int D_0017A87C;
extern char B_00188730[];
extern void func_00027EB8();
extern void *createScriptObj(void *, int, int, int, int, int, int, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

void FlushStageManager(int stage)
{
    int *cur = &D_0017A87C;

    if (*cur != stage) {
        isysAddGroupWithLinkParam(createScriptObj(func_00027EB8, stage, *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0), B_00188730, 0, 0);
        *cur = stage;
    }
}
