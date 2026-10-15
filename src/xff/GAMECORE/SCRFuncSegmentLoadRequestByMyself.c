extern int stagemanager_checkstageAlreadyLoadRequestedByStrptr(char *);
extern void stagemanager_loadstageByStrptrWithTargetObjectAreaCenter(char *, void *);

void SCRFuncSegmentLoadRequestByMyself(void *a, int b, int c, int d, int e, int f, char *name)
{
    if (!stagemanager_checkstageAlreadyLoadRequestedByStrptr(name))
        stagemanager_loadstageByStrptrWithTargetObjectAreaCenter(name, a);
}
