extern char *GetSCRCharaAIWorkPtr();

void SCRConditionPoseidonDamageFlagReset(void)
{
    char *w = GetSCRCharaAIWorkPtr();

    *(int *)(w + 0x41BC) = 0;
    *(int *)(w + 0x41D8) = 0;
}
