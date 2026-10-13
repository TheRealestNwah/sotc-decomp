extern void *getSCRDataCtrlWork();

int SCRConditionPlayerInSight(void)
{
    return (*(int *)((char *)(getSCRDataCtrlWork()) + 0x405C));
}
