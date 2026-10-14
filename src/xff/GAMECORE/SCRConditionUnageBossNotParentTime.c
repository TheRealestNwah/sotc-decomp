extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionUnageBossNotParentTime(void *actor, float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 < (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x5B30)))) {
        var_v0 = 0;
    }
    return var_v0;
}
