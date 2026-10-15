extern int D_00040624;

void iosResetCpuRapCounter(int mode)
{
    D_00040624 = mode;
    *(volatile int *)0x10000810 = mode | 0x80;
    *(volatile int *)0x10000800 = 0;
}
