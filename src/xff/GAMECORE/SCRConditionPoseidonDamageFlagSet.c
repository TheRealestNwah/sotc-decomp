extern void *GetSCRCharaAIWorkPtr(void *);

void SCRConditionPoseidonDamageFlagSet(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41BC)) = 1;
}
