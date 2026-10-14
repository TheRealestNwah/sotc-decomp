extern char *GetSCRCharaAIWorkPtr();

void SCRFuncPoseidonMissAttackInit(int a, int b)
{
    *(int *)(GetSCRCharaAIWorkPtr(a) + 0x41C4) = b;
}
