extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionMinoCAtkCountChack(int a, int n)
{
    return n < *(int *)(((char *)GetSCRCharaAIWorkPtr((void *)a)) + 0x41E8);
}
