int iosGetField(void)
{
    return (*(volatile unsigned long *)0x12001000 >> 13) & 1;
}
