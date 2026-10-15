extern int iosWaitDMA(void);

int iosSrpWaitDMA(void)
{
    __asm__ __volatile__("sync");
    return iosWaitDMA();
}
