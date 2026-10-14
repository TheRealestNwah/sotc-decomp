extern char gcGlobalVar[];

void ReleaseGame(int m)
{
    char *g = gcGlobalVar;

    *(int *)(g + 0x1AC) &= ~m;
}
