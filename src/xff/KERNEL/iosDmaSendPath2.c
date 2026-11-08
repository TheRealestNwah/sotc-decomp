extern void FlushCache(int mode);

void iosDmaSendPath2(long addr, long qwc)
{
    int stat;

    do {
        __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(stat));
    } while ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100) ||
             (*(volatile int *)0x10003C00 & 0x1F000003) || (stat & 0x100) ||
             (*(volatile int *)0x10003020 & 0xC00));
    *(volatile int *)0x10009020 = qwc;
    *(volatile int *)0x10009010 = addr & 0x0FFFFFFF;
    FlushCache(0);
    *(volatile int *)0x10009000 = 0x101;
}
