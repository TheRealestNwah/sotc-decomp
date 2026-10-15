extern volatile int B_000BF6E0;

void ischedStop(void)
{
    if (B_000BF6E0 == 0)
        *(volatile int *)0x10000010 &= ~0x80;
    B_000BF6E0++;
}
