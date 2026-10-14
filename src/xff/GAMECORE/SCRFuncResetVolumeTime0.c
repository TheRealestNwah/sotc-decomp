extern void *getSCRDataCtrlWork(void *);

void SCRFuncResetVolumeTime0(void *actor)
{
    (*(int *)((char *)(getSCRDataCtrlWork(actor)) + 0x40AC)) = 0;
}
