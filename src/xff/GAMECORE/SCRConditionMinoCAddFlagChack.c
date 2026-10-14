extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionMinoCAddFlagChack(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41EC));
}
