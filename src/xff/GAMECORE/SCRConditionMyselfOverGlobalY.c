extern void *GetLayoutClass(void *);

int SCRConditionMyselfOverGlobalY(void *actor, float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 <= (*(float *)((char *)((*(void **)((char *)(GetLayoutClass(actor)) + 0x134))) + 4)))) {
        var_v0 = 0;
    }
    return var_v0;
}
