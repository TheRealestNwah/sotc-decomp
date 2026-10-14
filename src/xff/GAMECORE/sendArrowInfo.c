extern void *GetSCRCharaAIWorkPtr(void *);

int sendArrowInfo(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x20));
}
