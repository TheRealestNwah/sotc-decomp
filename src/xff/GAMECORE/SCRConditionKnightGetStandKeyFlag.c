extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionKnightGetStandKeyFlag(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B0)) & 1;
}
