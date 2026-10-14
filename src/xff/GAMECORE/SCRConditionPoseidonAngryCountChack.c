extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionPoseidonAngryCountChack(int a, int n)
{
    return *(int *)(((char *)GetSCRCharaAIWorkPtr((void *)a)) + 0x41D0) < n;
}
