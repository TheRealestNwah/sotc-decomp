extern int getSCRDataCtrlWork();
extern int setGpCalcDist(int, float);

int SCRFuncSetGpCalcDist(float r)
{
    return setGpCalcDist(getSCRDataCtrlWork(), r);
}
