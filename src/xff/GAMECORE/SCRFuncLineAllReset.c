extern int getSCRDataCtrlWork();
extern int allResetLineAttr();

int SCRFuncLineAllReset(void)
{
    return allResetLineAttr(getSCRDataCtrlWork());
}
