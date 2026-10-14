extern int getSCRDataCtrlWork();
extern int setSearchRadius(int, float);

int SCRFuncSetSearchRadius(float r)
{
    return setSearchRadius(getSCRDataCtrlWork(), r);
}
