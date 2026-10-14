extern void *GetSCRCharaAIWorkPtr();
extern unsigned char gcGlobalVar[1];

void SCRFuncKirinFallRockMain(void)
{
    float temp_f0;
    float temp_f1;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    temp_f1 = (*(float *)((char *)(temp_v0) + 0x41B4));
    if (temp_f1 > 0.0f) {
        temp_f0 = temp_f1 - (*(float *)((char *)(&gcGlobalVar) + 0x180));
        (*(float *)((char *)(temp_v0) + 0x41B4)) = temp_f0;
        if (temp_f0 < 0.0f) {
            (*(float *)((char *)(temp_v0) + 0x41B4)) = 0.0f;
        }
    }
}
