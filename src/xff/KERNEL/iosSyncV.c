extern void waitVscheduler(void);

int iosSyncV(int n)
{
    int i;
    for (i = 0; i < n + 1; i++)
        waitVscheduler();
    return (*(volatile unsigned long *)0x12001000 >> 13) & 1;
}
