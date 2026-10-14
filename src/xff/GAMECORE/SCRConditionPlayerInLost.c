extern void *getSCRDataCtrlWork(void *);

int SCRConditionPlayerInLost(void *actor)
{
    return (*(int *)((char *)(getSCRDataCtrlWork(actor)) + 0x405C)) == 0;
}
