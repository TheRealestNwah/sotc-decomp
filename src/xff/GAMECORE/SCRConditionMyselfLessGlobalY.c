extern void *GetLayoutClass(void *);

int SCRConditionMyselfLessGlobalY(void *actor, float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!((*(float *)((char *)((*(void **)((char *)(GetLayoutClass(actor)) + 0x134))) + 4)) <= fparg0)) {
        var_v0 = 0;
    }
    return var_v0;
}
