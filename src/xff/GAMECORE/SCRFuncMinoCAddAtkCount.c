extern void *GetSCRCharaAIWorkPtr();

void SCRFuncMinoCAddAtkCount(void)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    (*(int *)((char *)(temp_v0) + 0x41E8)) = (int) ((*(int *)((char *)(temp_v0) + 0x41E8)) + 1);
}
