void setRouteAttackBirdCtrlWork(char *p)
{
    *(int *)(p + 0x30) = 1;
    *(int *)(p + 0x154) = 1;
}
