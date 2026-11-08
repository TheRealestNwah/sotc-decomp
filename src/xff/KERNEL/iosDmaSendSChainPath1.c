extern void FlushCache(int mode);

void iosDmaSendSChainPath1(void *tag)
{
    int stat;

    do {
        __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(stat));
    } while ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100) ||
             (*(volatile int *)0x10003C00 & 0x1F000003) || (stat & 0x100) ||
             (*(volatile int *)0x10003020 & 0xC00));
    *(volatile int *)0x10009020 = 0;
    *(volatile int *)0x10009030 = (int)tag & 0x7FFFFFFF;
    FlushCache(0);
    *(volatile int *)0x10009000 = 0x145;
}
