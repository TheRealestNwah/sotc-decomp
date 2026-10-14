extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncMinoCAddAtkCount(void *actor)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    (*(int *)((char *)(temp_v0) + 0x41E8)) = (int) ((*(int *)((char *)(temp_v0) + 0x41E8)) + 1);
}
