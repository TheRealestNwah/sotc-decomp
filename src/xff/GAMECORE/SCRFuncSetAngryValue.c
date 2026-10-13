extern void *getSCRDataCtrlWork();

void SCRFuncSetAngryValue(float fparg0)
{
    (*(float *)((char *)(getSCRDataCtrlWork()) + 0x40F8)) = fparg0;
}
