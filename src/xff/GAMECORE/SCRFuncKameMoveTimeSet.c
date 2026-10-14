extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKameMoveTimeSet(float fparg0)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    if ((*(float *)((char *)(temp_v0) + 0x41DC)) <= 0.0f) {
        (*(float *)((char *)(temp_v0) + 0x41DC)) = fparg0;
    }
}
