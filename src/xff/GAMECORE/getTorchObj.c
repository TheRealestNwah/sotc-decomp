extern void *GetSCRCharaAIWorkPtr(void *);

int getTorchObj(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x150));
}
