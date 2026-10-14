extern char *getSCRDataCtrlWork();
extern int IsHorseCalled_withFlgOff();

int SCRConditionHorseCalled(void)
{
    return IsHorseCalled_withFlgOff(*(int *)(getSCRDataCtrlWork() + 0x4078));
}
