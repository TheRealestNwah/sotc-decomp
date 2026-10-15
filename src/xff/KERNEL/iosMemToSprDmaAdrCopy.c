void iosMemToSprDmaAdrCopy(int madr, int qwc, int sadr)
{
    *(volatile int *)0x1000E020 = -0x400;
    *(volatile int *)0x1000E010 = 0x200;
    *(volatile int *)0x1000D410 = madr;
    *(volatile int *)0x1000D420 = qwc;
    *(volatile int *)0x1000D480 = sadr;
    *(volatile int *)0x1000E020 |= 0x200;
    *(volatile int *)0x1000D400 = 0x101;
}
