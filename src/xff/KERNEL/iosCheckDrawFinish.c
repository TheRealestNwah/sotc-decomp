extern int D_00040B3C;

int iosCheckDrawFinish(void)
{
    int stat;

    D_00040B3C++;
    __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(stat));
    if ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100) ||
        (*(volatile int *)0x10003C00 & 0x1F000003) || (stat & 0x100) || (*(volatile int *)0x10003020 & 0xC00))
        return 0;
    return 1;
}
