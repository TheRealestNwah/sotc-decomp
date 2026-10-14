extern char *GetSCRCharaAIWorkPtr();

void SCRFuncNargaSetPlayerDamage(int a, int b)
{
    *(int *)(GetSCRCharaAIWorkPtr(a) + 0x5AA4) = b;
}
