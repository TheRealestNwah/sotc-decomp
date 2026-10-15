extern volatile long B_0004F5E0;

long iosGetTCountExtension(void)
{
    return B_0004F5E0 | (unsigned int)*(volatile int *)0x10000000;
}
