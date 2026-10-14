extern char *getSCRDataCtrlWork();
extern int IsHorseCalled_withFlgOff(void *);

int SCRConditionHorseCalled(void)
{
    return IsHorseCalled_withFlgOff(*(void **)(getSCRDataCtrlWork() + 0x4078));
}
