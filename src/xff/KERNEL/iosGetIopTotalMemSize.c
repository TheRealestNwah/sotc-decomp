extern int LoaderSysCheckCDBootMode();

int iosGetIopTotalMemSize(void)
{
    return LoaderSysCheckCDBootMode() == 0 ? 0x800000 : 0x200000;
}
