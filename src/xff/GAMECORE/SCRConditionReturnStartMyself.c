extern void *getSCRDataCtrlWork(void *);

int SCRConditionReturnStartMyself(void *actor)
{
    return (*(int *)((char *)(getSCRDataCtrlWork(actor)) + 0x4198));
}
