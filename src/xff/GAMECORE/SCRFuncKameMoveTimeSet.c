extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKameMoveTimeSet(void *actor, float fparg0)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    if ((*(float *)((char *)(temp_v0) + 0x41DC)) <= 0.0f) {
        (*(float *)((char *)(temp_v0) + 0x41DC)) = fparg0;
    }
}
