extern void *getSCRDataCtrlWork();

int SCRConditionPlayerInLost(void)
{
    return (*(int *)((char *)(getSCRDataCtrlWork()) + 0x405C)) == 0;
}
