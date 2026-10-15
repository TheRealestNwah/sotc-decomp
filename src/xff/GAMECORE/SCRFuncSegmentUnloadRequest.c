extern int stagemanager_checkstageAlreadyLoadRequestedByStrptr(char *);
extern void stagemanager_unloadstageByStrptr(char *);

void SCRFuncSegmentUnloadRequest(void *actor, int a, int b, int c, int d, int e, char *name)
{
    if (stagemanager_checkstageAlreadyLoadRequestedByStrptr(name))
        stagemanager_unloadstageByStrptr(name);
}
