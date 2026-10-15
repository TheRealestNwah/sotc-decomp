extern char gcGlobalVar[];
extern void func_0002D570();
extern void *createScriptObj(void *, int, int, int, int, int, int, int);

void stagemanager_loadstage(int a, int b)
{
    void *o = createScriptObj(func_0002D570, (a << 16) | b, *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0);
    o = 0;
}
