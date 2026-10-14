extern int getSCRDataCtrlWork();
extern int resetPassageWork();

int SCRFuncResetPathSystem(void)
{
    return resetPassageWork(getSCRDataCtrlWork());
}
