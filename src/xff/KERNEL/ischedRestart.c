extern volatile int B_000BF6E0;

void ischedRestart(void)
{
    B_000BF6E0--;
    if (B_000BF6E0 == 0)
        *(volatile int *)0x10000010 |= 0x80;
}
