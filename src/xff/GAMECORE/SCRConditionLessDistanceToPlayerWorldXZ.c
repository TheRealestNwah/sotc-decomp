extern void *getSCRDataCtrlWork(void *);

int SCRConditionLessDistanceToPlayerWorldXZ(void *actor, float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!((*(float *)((char *)(getSCRDataCtrlWork(actor)) + 0x4080)) <= fparg0)) {
        var_v0 = 0;
    }
    return var_v0;
}
