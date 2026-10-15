extern char gcGlobalVar[];

void *getColiGroupByUserPathWork(char *w)
{
    int v = *(int *)(w + 0x3C50);
    if (v == 0)
        return gcGlobalVar + 0x238;
    if (v == 1)
        return gcGlobalVar + 0x234;
    return 0;
}
