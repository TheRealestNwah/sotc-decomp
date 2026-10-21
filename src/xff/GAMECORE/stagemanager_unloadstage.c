extern char gcGlobalVar[];
extern void func_0002D680(int);
extern void *createScriptObj(void (*)(int), int, int, int, int, int, int, int);

void stagemanager_unloadstage(int s)
{
    void *o = createScriptObj(func_0002D680, s, *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0);
    o = 0;
}
