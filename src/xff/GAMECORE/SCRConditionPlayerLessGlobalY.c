extern void *getSCRDataCtrlWork(void *);

int SCRConditionPlayerLessGlobalY(void *actor, float fparg0)
{
    int var_a0;

    var_a0 = 1;
    if (!((*(float *)((char *)((*(void **)((char *)((*(void **)((char *)(getSCRDataCtrlWork(actor)) + 0x407C))) + 0x134))) + 4)) <= fparg0)) {
        var_a0 = 0;
    }
    return var_a0;
}
