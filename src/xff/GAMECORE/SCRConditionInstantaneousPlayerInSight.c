extern void *getSCRDataCtrlWork();

int SCRConditionInstantaneousPlayerInSight(void)
{
    return (*(long *)((char *)(getSCRDataCtrlWork()) + 0x4060)) != 0;
}
