extern void *getSCRDataCtrlWork();

int SCRConditionReturnStartMyself(void)
{
    return (*(int *)((char *)(getSCRDataCtrlWork()) + 0x4198));
}
