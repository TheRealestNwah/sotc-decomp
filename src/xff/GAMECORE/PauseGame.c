extern char gcGlobalVar[];
extern int func_0000BB50();

int PauseGame(int m)
{
    char *g = gcGlobalVar;

    *(int *)(g + 0x1AC) |= m;
    return func_0000BB50();
}
