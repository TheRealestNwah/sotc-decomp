extern int stagemanager_checkstageAlreadyLoadRequestedByStrptr(char *);
extern void setLoadingCheckFunc(void *, char *);

void SCRFuncSegmentLoadWait(void *actor, int a, int b, int c, int d, int e, char *name)
{
    if (!stagemanager_checkstageAlreadyLoadRequestedByStrptr(name))
        setLoadingCheckFunc(stagemanager_checkstageAlreadyLoadRequestedByStrptr, name);
}
