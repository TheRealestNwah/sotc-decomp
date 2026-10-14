extern void *GetSCRCharaAIWorkPtr();

int SCRConditionBirdPassingEachOther(void)
{
    int var_v1;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    var_v1 = 1;
    if (!((*(float *)((char *)(temp_v0) + 0x41D8)) < (*(float *)((char *)(temp_v0) + 0x41D4)))) {
        var_v1 = 0;
    }
    return var_v1;
}
