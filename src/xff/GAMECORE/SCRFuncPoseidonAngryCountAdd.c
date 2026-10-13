extern void *GetSCRCharaAIWorkPtr();

void SCRFuncPoseidonAngryCountAdd(void)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    (*(int *)((char *)(temp_v0) + 0x41D0)) = (int) ((*(int *)((char *)(temp_v0) + 0x41D0)) + 1);
}
