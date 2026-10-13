extern void *GetSCRCharaAIWorkPtr();

void SCRConditionPoseidonDamageFlagSet(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41BC)) = 1;
}
