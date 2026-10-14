extern int InitTwoWayLink();

int InitSecureParentInfo(char *p)
{
    *(int *)(p + 0x4C) = 0;
    return InitTwoWayLink(p + 0x40, p + 0x4C);
}
