extern char *GetSCRCharaAIWorkPtr();

int SCRConditionMinoCAtkCountChack(int a, int n)
{
    return n < *(int *)(GetSCRCharaAIWorkPtr() + 0x41E8);
}
