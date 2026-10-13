extern void *GetSCRCharaAIWorkPtr();

int SCRConditionPoseidonGetRevolutionRayChack(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41B0));
}
