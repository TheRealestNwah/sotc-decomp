extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionLeoCheckArmorBroken(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41C0)) != 0;
}
