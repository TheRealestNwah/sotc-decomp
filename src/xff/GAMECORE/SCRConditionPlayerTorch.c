extern char *getSCRDataCtrlWork();
extern int getTorchInfo(void *);

int SCRConditionPlayerTorch(void)
{
    return getTorchInfo(*(void **)(getSCRDataCtrlWork() + 0x4078));
}
