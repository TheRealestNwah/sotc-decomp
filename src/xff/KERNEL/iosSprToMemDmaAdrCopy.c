void iosSprToMemDmaAdrCopy(int madr, int qwc, int sadr)
{
    *(volatile int *)0x1000E020 = -0x400;
    *(volatile int *)0x1000E010 = 0x100;
    *(volatile int *)0x1000D010 = madr;
    *(volatile int *)0x1000D020 = qwc;
    *(volatile int *)0x1000D080 = sadr;
    *(volatile int *)0x1000E020 |= 0x100;
    *(volatile int *)0x1000D000 = 0x100;
}
