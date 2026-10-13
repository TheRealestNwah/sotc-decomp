extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKnightSetStand(void)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    (*(int *)((char *)(temp_v0) + 0x41B0)) = (int) ((*(int *)((char *)(temp_v0) + 0x41B0)) | 1);
}
