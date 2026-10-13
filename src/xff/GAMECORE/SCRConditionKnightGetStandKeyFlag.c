extern void *GetSCRCharaAIWorkPtr();

int SCRConditionKnightGetStandKeyFlag(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41B0)) & 1;
}
