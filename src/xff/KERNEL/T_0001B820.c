extern int B_000BF704;
extern void iosiWakeupThread(int);

static int T_0001B820(void)
{
    iosiWakeupThread(B_000BF704);
    __asm__ volatile("sync\n\tei");
    return 0;
}
