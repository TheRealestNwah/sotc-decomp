extern void *getSCRDataCtrlWork();

void SCRFuncAddAngryValue(float fparg0)
{
    void *temp_v0;

    temp_v0 = getSCRDataCtrlWork();
    (*(float *)((char *)(temp_v0) + 0x40F8)) = (float) ((*(float *)((char *)(temp_v0) + 0x40F8)) + fparg0);
}
