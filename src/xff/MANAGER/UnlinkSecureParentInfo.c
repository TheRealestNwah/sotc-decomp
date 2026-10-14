extern void DeleteTwoWayLink(void *);
void UnlinkSecureParentInfo(char *p)
{
    if (*(int *)(p + 0x4C) != 0) {
        *(int *)(p + 0x4C) = 0;
        DeleteTwoWayLink(p + 0x40);
    }
}
