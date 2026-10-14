extern int func_000FE618();

int _resetBaseMoveWork(int a, char *p)
{
    *(int *)(p + 0x4) = 0;
    *(int *)(p + 0x24) = 0;
    return func_000FE618(p);
}
