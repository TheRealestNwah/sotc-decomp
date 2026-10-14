extern void *getSCRDataCtrlWork(void *);

int SCRConditionPlayerInSight(void *actor)
{
    return (*(int *)((char *)(getSCRDataCtrlWork(actor)) + 0x405C));
}
