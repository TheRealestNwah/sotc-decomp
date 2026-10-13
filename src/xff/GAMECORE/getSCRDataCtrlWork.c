extern int GetSCRCharaAIWorkPtr();

int getSCRDataCtrlWork(void)
{
    return (GetSCRCharaAIWorkPtr() + 0x13) & ~0xF;
}
