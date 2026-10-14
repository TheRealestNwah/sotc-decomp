void ColCont_Reset(char *p)
{
    *(int *)(p + 0x8) = 0;
    *(long *)(p + 0x0) = 0;
}
