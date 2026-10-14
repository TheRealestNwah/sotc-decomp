extern void *GetLayoutClass();

int SCRConditionMyselfLessGlobalY(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!((*(float *)((char *)((*(void **)((char *)(GetLayoutClass()) + 0x134))) + 4)) <= fparg0)) {
        var_v0 = 0;
    }
    return var_v0;
}
