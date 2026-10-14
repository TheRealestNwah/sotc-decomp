extern void *getSCRDataCtrlWork(void *);

void SCRFuncAddAngryValue(void *actor, float fparg0)
{
    void *temp_v0;

    temp_v0 = getSCRDataCtrlWork(actor);
    (*(float *)((char *)(temp_v0) + 0x40F8)) = (float) ((*(float *)((char *)(temp_v0) + 0x40F8)) + fparg0);
}
