extern void *GetSCRCharaAIWorkPtr();

void SCRFuncYamoriBSetRandomRadius(float fparg0, float fparg1)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    (*(float *)((char *)(temp_v0) + 0x41D8)) = fparg0;
    (*(float *)((char *)(temp_v0) + 0x41DC)) = fparg1;
    (*(int *)((char *)(temp_v0) + 0x41D0)) = 1;
    (*(int *)((char *)(temp_v0) + 0x41D4)) = 0;
}
