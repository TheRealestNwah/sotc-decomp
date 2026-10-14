extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionPoseidonGetRevolutionRayChack(void *actor)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41B0));
}
