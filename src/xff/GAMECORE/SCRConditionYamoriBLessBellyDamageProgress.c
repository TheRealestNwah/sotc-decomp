extern void *GetSCRCharaAIWorkPtr();

int SCRConditionYamoriBLessBellyDamageProgress(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!((*(float *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41E4)) <= fparg0)) {
        var_v0 = 0;
    }
    return var_v0;
}
