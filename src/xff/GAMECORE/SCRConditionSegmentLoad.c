extern long stagemanager_checkstageAlreadyLoadedByStrptr(unsigned int *);
long SCRConditionSegmentLoad(int a, int b, int c, int d, int e, int f, int g, int h, unsigned int *reference)
{
    return stagemanager_checkstageAlreadyLoadedByStrptr(reference);
}
