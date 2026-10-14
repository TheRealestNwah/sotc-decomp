extern char *GetSCRCharaAIWorkPtr();

int SCRConditionPoseidonAngryCountChack(int a, int n)
{
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x41D0) < n;
}
