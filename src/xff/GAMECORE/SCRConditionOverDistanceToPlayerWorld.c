extern void *getSCRDataCtrlWork(void *);

int SCRConditionOverDistanceToPlayerWorld(void *actor, float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 <= (*(float *)((char *)(getSCRDataCtrlWork(actor)) + 0x4084)))) {
        var_v0 = 0;
    }
    return var_v0;
}
