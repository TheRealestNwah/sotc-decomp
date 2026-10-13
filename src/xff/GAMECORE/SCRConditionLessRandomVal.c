extern void *getSCRDataCtrlWork();

int SCRConditionLessRandomVal(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!((*(float *)((char *)(getSCRDataCtrlWork()) + 0x40B4)) <= fparg0)) {
        var_v0 = 0;
    }
    return var_v0;
}
