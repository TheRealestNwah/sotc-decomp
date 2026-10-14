extern unsigned int opFlag;

int opflowChkTitleDemoStart(void)
{
    return ((unsigned int) opFlag >> 4) & 1;
}
