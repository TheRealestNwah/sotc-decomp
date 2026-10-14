extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKnightSetStand(void *actor)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    (*(int *)((char *)(temp_v0) + 0x41B0)) = (int) ((*(int *)((char *)(temp_v0) + 0x41B0)) | 1);
}
