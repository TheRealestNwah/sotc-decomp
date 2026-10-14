extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKameNextAtkTimeInit(void *actor, float fparg0)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    if ((*(float *)((char *)(temp_v0) + 0x41E0)) < 0.0f) {
        (*(float *)((char *)(temp_v0) + 0x41E0)) = fparg0;
    }
}
