extern void *getSCRDataCtrlWork();

void SCRFuncResetVolumeTime0(void)
{
    (*(int *)((char *)(getSCRDataCtrlWork()) + 0x40AC)) = 0;
}
