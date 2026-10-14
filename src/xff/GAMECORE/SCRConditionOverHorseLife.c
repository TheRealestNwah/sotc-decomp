extern void *GetSCRCharaAIWorkPtr(void *);

int SCRConditionOverHorseLife(void *actor, float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 <= (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x4220)))) {
        var_v0 = 0;
    }
    return var_v0;
}
