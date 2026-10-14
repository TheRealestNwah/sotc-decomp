void DirectTurn_Reset(char *p)
{
    *(char *)(p + 0x14) = 0;
    *(int *)(p + 0x10) = 0;
}
