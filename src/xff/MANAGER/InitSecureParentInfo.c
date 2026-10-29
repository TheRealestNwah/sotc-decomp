extern void InitTwoWayLink(char *, int);

void InitSecureParentInfo(char *info)
{
    *(int *)(info + 0x4C) = 0;
    InitTwoWayLink(info + 0x40, (int)(info + 0x4C));
}
