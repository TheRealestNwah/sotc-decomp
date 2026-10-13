extern void *GetSCRCharaAIWorkPtr();

int SCRConditionPoseidonMissAttackCheck(void)
{
    return (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41C4)) < 1;
}
