extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionPoseidonMissAttackCheck(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41C4)) < 1;
}
