void InitTwoWayLink(char *p, int a1)
{
    *(int *)(p + 0x8) = a1;
    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x4) = 0;
}
