extern char *getSCRDataCtrlWork(void *);

int SCRConditionKameNextTime(void *actor, int n)
{
    return (int)*(float *)(getSCRDataCtrlWork(actor) + 0x40A4) % n < 1;
}
