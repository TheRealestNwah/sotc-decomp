extern char gcGlobalVar[];

char *GetPlayerControlButtonContext(void)
{
    return gcGlobalVar + 0x314;
}
