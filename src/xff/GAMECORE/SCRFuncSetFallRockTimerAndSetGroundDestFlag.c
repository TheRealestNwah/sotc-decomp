extern void *GetSCRCharaAIWorkPtr(int);
extern int SCRGetFirstObj(void *);
extern unsigned char gcGlobalVar[1];

void SCRFuncSetFallRockTimerAndSetGroundDestFlag(void)
{
    float temp_f0;
    int temp_v0;
    void *temp_v0_2;

    temp_v0 = SCRGetFirstObj(&gcGlobalVar + 0x2B8);
    if (temp_v0 != 0) {
        temp_v0_2 = GetSCRCharaAIWorkPtr(temp_v0);
        if ((*(int *)((char *)(temp_v0_2) + 0x41B8)) != 0) {
            temp_f0 = (*(float *)((char *)(temp_v0_2) + 0x41B4)) + 0.5f;
            (*(float *)((char *)(temp_v0_2) + 0x41B4)) = temp_f0;
            if (temp_f0 > 5.0f) {
                (*(float *)((char *)(temp_v0_2) + 0x41B4)) = 5.0f;
            }
            (*(int *)((char *)(temp_v0_2) + 0x41BC)) = 1;
        }
    }
}
