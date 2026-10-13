extern void *GetSCRCharaAIWorkPtr();

void SCRFuncPoseidonMissAttackAdd(void)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    (*(int *)((char *)(temp_v0) + 0x41C4)) = (int) ((*(int *)((char *)(temp_v0) + 0x41C4)) - 1);
}
