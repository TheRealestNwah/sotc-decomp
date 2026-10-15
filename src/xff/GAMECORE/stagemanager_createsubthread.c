extern char gcGlobalVar[];
extern char B_00188730[];
extern void *createScriptObj(void *, void *, int, int, int, int, int, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

void *stagemanager_createsubthread(void *a, void *b, int link)
{
    void *o = createScriptObj(a, b, *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0);
    if (link != 0)
        isysAddGroupWithLinkParam(o, B_00188730, 0, 0);
    return o;
}
