extern void *getSCRDataCtrlWork(void *);

int SCRConditionInstantaneousPlayerInSight(void *actor)
{
    return (*(long *)((char *)(getSCRDataCtrlWork(actor)) + 0x4060)) != 0;
}
