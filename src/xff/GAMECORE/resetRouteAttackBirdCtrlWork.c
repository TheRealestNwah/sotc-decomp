void resetRouteAttackBirdCtrlWork(char *p)
{
    *(int *)(p + 0x30) = 0;
    *(int *)(p + 0x154) = 0;
}
