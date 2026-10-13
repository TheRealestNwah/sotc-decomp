extern void *GetLayoutClass();

int SCRConditionMyselfOverGlobalY(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 <= (*(float *)((char *)((*(void **)((char *)(GetLayoutClass()) + 0x134))) + 4)))) {
        var_v0 = 0;
    }
    return var_v0;
}
