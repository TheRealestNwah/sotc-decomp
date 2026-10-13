extern void *GetSCRCharaAIWorkPtr();

void SCRFuncKnightSetShakeStop(void)
{
    int temp_v0_2;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    temp_v0_2 = (*(int *)((char *)(temp_v0) + 0x41B0));
    if (!(temp_v0_2 & 4)) {
        (*(int *)((char *)(temp_v0) + 0x41B0)) = (int) (temp_v0_2 | 4);
    }
}
