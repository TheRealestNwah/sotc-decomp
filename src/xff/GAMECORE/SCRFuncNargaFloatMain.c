extern void *getSCRDataCtrlWork();
extern void setOffsetParamWormCtrlWork(int, void *, int, float, float);

void SCRFuncNargaFloatMain(int arg0, float fparg0, float fparg1, float fparg2)
{
    float temp_f1;
    float var_f12;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = getSCRDataCtrlWork();
    temp_f1 = (*(float *)((char *)(temp_v0) + 0x40A4));
    temp_v0_2 = temp_v0 + 0x3D10;
    var_f12 = fparg0;
    if (temp_f1 < fparg2) {
        var_f12 = ((var_f12 - fparg1) * (temp_f1 / fparg2)) + fparg1;
    }
    setOffsetParamWormCtrlWork(arg0, temp_v0_2, (*(int *)((char *)(temp_v0_2) + 0xBC)), var_f12, (*(float *)((char *)(temp_v0_2) + 0xC4)));
}
