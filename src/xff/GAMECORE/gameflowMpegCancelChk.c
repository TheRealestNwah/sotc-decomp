extern char padManagerData[];

int gameflowMpegCancelChk(void)
{
    return (*(int *)(padManagerData + 0x8) >> 11) & 1;
}
