extern void *getSCRDataCtrlWork();

int SCRConditionOverAngryValue(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 <= (*(float *)((char *)(getSCRDataCtrlWork()) + 0x40F8)))) {
        var_v0 = 0;
    }
    return var_v0;
}
