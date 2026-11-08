typedef int s128 __attribute__((mode(TI)));
extern s128 D_00040B50[2];

/* Parked: 19 words differ; original rematerializes the constant 1 instead of reusing it */
#ifdef NONMATCHING
void iosResetPath(void)
{
    int v = 0;

    *(volatile int *)0x10003C10 = 1;
    __asm__ __volatile__(
        "cfc2.ni %0, $vi28\n"
        "\tori %0, %0, 0x200\n"
        "\tctc2.ni %0, $vi28\n"
        "\tsync.p"
        : "+r"(v));
    *(volatile s128 *)0x10005000 = D_00040B50[0];
    *(volatile s128 *)0x10005000 = D_00040B50[1];
    *(volatile int *)0x10003000 = 1;
}
#else
extern void iosResetPath(void);
#endif
