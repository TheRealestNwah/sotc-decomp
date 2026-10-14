extern char *getSCRDataCtrlWork();
extern int getTorchInfo();

int SCRConditionPlayerTorch(void)
{
    return getTorchInfo(*(int *)(getSCRDataCtrlWork() + 0x4078));
}
