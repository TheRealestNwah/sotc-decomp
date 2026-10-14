extern char *getSCRDataCtrlWork();

void SCRFuncParentRelateInit(void)
{
    int *w = (int *)(getSCRDataCtrlWork() + 0x40D8);

    w[0] = 0;
    w[1] = 0;
}
