extern void *getSCRDataCtrlWork(void *);
extern int getTorchInfo(void *);

int SCRConditionPlayerTorch(void *actor)
{
    return getTorchInfo(*(void **)(((char *)getSCRDataCtrlWork(actor)) + 0x4078));
}
