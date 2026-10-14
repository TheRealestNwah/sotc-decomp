extern void *GetSCRCharaAIWorkPtr();

void SCRFuncUnageIncTblIdx(void)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    (*(int *)((char *)(temp_v0) + 0x5ACC)) = (int) (((*(int *)((char *)(temp_v0) + 0x5ACC)) + 0x11) & 0x1F);
}
