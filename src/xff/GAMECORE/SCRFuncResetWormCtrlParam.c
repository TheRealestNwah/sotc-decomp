extern void *getSCRDataCtrlWork(void *);
extern void resetVelocityWormCtrlWork(int, void *);

void SCRFuncResetWormCtrlParam(int arg0)
{
    void *temp_v0;

    temp_v0 = getSCRDataCtrlWork((void *)arg0);
    if ((*(int *)((char *)(temp_v0) + 0x4090)) == 3) {
        resetVelocityWormCtrlWork(arg0, temp_v0 + 0x3D10);
    }
}
