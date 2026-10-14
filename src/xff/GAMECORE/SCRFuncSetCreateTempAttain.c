extern int getSCRDataCtrlWork();
extern int setCreateTempAttain();

int SCRFuncSetCreateTempAttain(int a, int b)
{
    return setCreateTempAttain(getSCRDataCtrlWork(), b);
}
