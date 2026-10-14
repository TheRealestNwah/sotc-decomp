extern void *getSCRDataCtrlWork(void *);

int SCRConditionVolumeTime0(void *actor, float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 <= (*(float *)((char *)(getSCRDataCtrlWork(actor)) + 0x40AC)))) {
        var_v0 = 0;
    }
    return var_v0;
}
