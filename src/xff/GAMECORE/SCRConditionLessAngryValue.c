extern void *getSCRDataCtrlWork();

int SCRConditionLessAngryValue(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!((*(float *)((char *)(getSCRDataCtrlWork()) + 0x40F8)) <= fparg0)) {
        var_v0 = 0;
    }
    return var_v0;
}
