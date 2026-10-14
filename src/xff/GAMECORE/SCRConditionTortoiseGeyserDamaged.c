extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionTortoiseGeyserDamaged(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B0));
}
