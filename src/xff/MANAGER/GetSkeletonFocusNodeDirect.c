int GetSkeletonFocusNodeDirect(char *p)
{
    if (p == 0) {
        return -1;
    }
    return *(int *)(p + 0x8);
}
