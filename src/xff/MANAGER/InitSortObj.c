void InitSortObj(char *p, int a1)
{
    *(int *)(p + 0x0) = a1;
    *(int *)(p + 0xC) = 0;
    *(int *)(p + 0x8) = 0;
}
