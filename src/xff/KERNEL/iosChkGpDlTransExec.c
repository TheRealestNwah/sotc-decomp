int iosChkGpDlTransExec(void)
{
    int r = 0;
    if ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100))
        r = 1;
    return r;
}
